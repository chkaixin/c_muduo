#include "muduo/base/Thread.h"
#include "muduo/base/CurrentThread.h"
#include "muduo/base/Exception.h"
// #include "muduo/base/Logging.h"

#include <type_traits>

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/prctl.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <linux/unistd.h>

namespace muduo
{
namespace detail
{

pid_t gettid()
{
    return static_cast<pid_t>(::syscall(SYS_gettid));
}

void afterFork()
{
    muduo::CurrentThread::t_cachedTid = 0;
    muduo::CurrentThread::t_threadName = "main";
    CurrentThread::tid();
}

class ThreadNameInitializer
{
public:
    ThreadNameInitializer()
    {
        muduo::CurrentThread::t_threadName = "main";
        CurrentThread::tid();
        pthread_atfork(NULL, NULL, &afterFork);
    }
};

ThreadNameInitializer init;

struct ThreadData
{
    typedef muduo::Thread::ThreadFunc ThreadFunc;
    ThreadFunc func_;
    string name_;
    pid_t* tid_;
    // CountDownLatch* latch_;

    ThreadData(ThreadFunc func,
               const string& name,
               pid_t* tid
               /*CountDownLatch* latch*/)
    : func_(std::move(func)),
      name_(name),
      tid_(tid)
    //   latch_(latch)
    { }

    void runInThread()
    {
        *tid_ = muduo::CurrentThread::tid();
        tid_ = NULL;
        // latch_->countDown();
        // latch_ = NULL;

        muduo::CurrentThread::t_threadName = name_.empty() ? "muduoThrad" : name_.c_str();
        ::prctl(PR_SET_NAME, muduo::CurrentThread::t_threadName);
        
    }
}


}
} // namespace muduo