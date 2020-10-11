/* study extension for PHP */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_study.h"

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif

/* {{{ void study_test1()
 */
PHP_FUNCTION(study_test1)
{
	ZEND_PARSE_PARAMETERS_NONE();

	php_printf("The extension %s is loaded and working!\r\n", "study");
}
/* }}} */

/* {{{ string study_test2( [ string $var ] )
 */
PHP_FUNCTION(study_test2)
{
	char *var = "World";
	size_t var_len = sizeof("World") - 1;
	zend_string *retval;

	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_STRING(var, var_len)
	ZEND_PARSE_PARAMETERS_END();

	retval = strpprintf(0, "Hello %s", var);

	RETURN_STR(retval);
}
/* }}}*/

PHP_MINIT_FUNCTION(study)
{
	php_printf("MINIT\n");
	study_coroutine_util_init();
	return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(study)
{
	php_printf("MSHUTDOWN\n");
	return SUCCESS;
}

/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(study)
{
#if defined(ZTS) && defined(COMPILE_DL_STUDY)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	php_printf("RINIT\n");
	return SUCCESS;
}
/* }}} */


PHP_RSHUTDOWN_FUNCTION(study)
{
	php_printf("RSHUTDOWN\n");
	return SUCCESS;
}

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(study)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "study support", "enabled");
	php_info_print_table_end();
}
/* }}} */

/* {{{ arginfo
 */
ZEND_BEGIN_ARG_INFO(arginfo_study_test1, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_study_test2, 0)
	ZEND_ARG_INFO(0, str)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ study_functions[]
 */
static const zend_function_entry study_functions[] = {
	PHP_FE(study_test1,		arginfo_study_test1)
	PHP_FE(study_test2,		arginfo_study_test2)
	PHP_FE_END
};
/* }}} */

/* {{{ study_module_entry
 */
zend_module_entry study_module_entry = {
	STANDARD_MODULE_HEADER,
	"study",					/* Extension name */
	study_functions,			/* zend_function_entry */
	PHP_MINIT(study),							/* PHP_MINIT - Module initialization */
	PHP_MSHUTDOWN(study),							/* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(study),			/* PHP_RINIT - Request initialization */
	PHP_RSHUTDOWN(study),							/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(study),			/* PHP_MINFO - Module info */
	PHP_STUDY_VERSION,		/* Version */
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_STUDY
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(study)
#endif

