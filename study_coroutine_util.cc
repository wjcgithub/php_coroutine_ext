#include "study_coroutine.h"

using Study::PHPCoroutine;

ZEND_BEGIN_ARG_INFO_EX(arginfo_study_coroutine_create, 0, 0, 1)
    ZEND_ARG_CALLABLE_INFO(0, FUNC, 0)
ZEND_END_ARG_INFO()

static PHP_METHOD(study_coroutine_util, create)
{
    zend_fcall_info fci = empty_fcall_info;
    zend_fcall_info_cache fcc = empty_fcall_info_cache;
    zval result;

    ZEND_PARSE_PARAMETERS_START(1, -1)
        Z_PARAM_FUNC(fci, fcc)
        Z_PARAM_VARIADIC('*', fci.params, fci.param_count)
    ZEND_PARSE_PARAMETERS_END_EX(RETURN_FALSE);

    PHPCoroutine::create(&fcc, fci.param_count, fci.params);

    // fci.retval = &result;
    // if (zend_call_function(&fci, &fcc) != SUCCESS)
    // {
    //     return;
    // }
    
    // *return_value = result;

    php_printf("study coroutine created success! \n");
}
//void zim_study_coroutine_util_create(zend_execute_data *execute_data, zval *return_value);

const zend_function_entry study_coroutine_util_methods[] = 
{
    PHP_ME(study_coroutine_util, create, arginfo_study_coroutine_create, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_FE_END
};

zend_class_entry study_coroutine_ce;
zend_class_entry *study_coroutine_ce_ptr;

void study_coroutine_util_init()
{
    //初始化类
    INIT_NS_CLASS_ENTRY(study_coroutine_ce, "Study", "Coroutine", study_coroutine_util_methods);
    //将类实体注册到zend引擎
    study_coroutine_ce_ptr = zend_register_internal_class(&study_coroutine_ce TSRMLS_CC);
}