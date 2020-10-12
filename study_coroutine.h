#ifndef STUDY_COROUTINE_H
#define STUDY_COROUTINE_H

#include "php_study.h"

struct php_coro_args
{
    zend_fcall_info_cache *fci_cache;
    zval *argv;
    uint32_t argc;
};

struct php_coro_task
{
    zval *vm_stack_top;   //协程栈顶
    zval *vm_stack_end;   //协程栈底
    zend_vm_stack vm_stack;  //协程栈指针
    size_t vm_stack_page_size;  //协程栈页大小
    zend_execute_data *execute_data; //当前协程栈栈帧
};

namespace Study
{
    class PHPCoroutine
    {
        public:
            static long create(zend_fcall_info_cache *fci_cache, uint32_t argc, zval *argv);
        
        protected:
            static void save_task(php_coro_task *task);
            static void save_vm_stack(php_coro_task *task);
            static php_coro_task* get_task();
    };
}

#endif    /* STUDY_COROUTINE_H */