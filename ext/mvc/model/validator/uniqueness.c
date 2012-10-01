
/*
  +------------------------------------------------------------------------+
  | Phalcon Framework                                                      |
  +------------------------------------------------------------------------+
  | Copyright (c) 2011-2012 Phalcon Team (http://www.phalconphp.com)       |
  +------------------------------------------------------------------------+
  | This source file is subject to the New BSD License that is bundled     |
  | with this package in the file docs/LICENSE.txt.                        |
  |                                                                        |
  | If you did not receive a copy of the license and are unable to         |
  | obtain it through the world-wide-web, please send an email             |
  | to license@phalconphp.com so we can send you a copy immediately.       |
  +------------------------------------------------------------------------+
  | Authors: Andres Gutierrez <andres@phalconphp.com>                      |
  |          Eduar Carvajal <eduar@phalconphp.com>                         |
  +------------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_phalcon.h"
#include "phalcon.h"

#include "Zend/zend_operators.h"
#include "Zend/zend_exceptions.h"
#include "Zend/zend_interfaces.h"

#include "kernel/main.h"
#include "kernel/memory.h"

#include "kernel/fcall.h"
#include "kernel/array.h"
#include "kernel/concat.h"
#include "kernel/exception.h"
#include "kernel/operators.h"
#include "kernel/object.h"

/**
 * Phalcon\Mvc\Model\Validator\Uniqueness
 *
 * Validates that a field or a combination of a set of fields are not
 * present more than once in the existing records of the related table
 *
 *<code>
 *use Phalcon\Mvc\Model\Validator\Uniqueness as UniquenessValidator;
 *
 *class Subscriptors extends Phalcon\Mvc\Model
 *{
 *
 *  public function validation()
 *  {
 *      $this->validate(new UniquenessValidator(array(
 *          'field' => 'email'
 *      )));
 *      if ($this->validationHasFailed() == true) {
 *          return false;
 *      }
 *  }
 *
 *}
 *</code>
 *
 */

/**
 * Executes the validator
 *
 * @return boolean
 */
PHP_METHOD(Phalcon_Mvc_Model_Validator_Uniqueness, validate){

	zval *record = NULL, *option = NULL, *field = NULL, *dependency_injector = NULL;
	zval *service = NULL, *meta_data = NULL, *bind_types = NULL, *bind_data_types = NULL;
	zval *conditions = NULL, *placeholders = NULL, *number = NULL, *compose_field = NULL;
	zval *exception_message = NULL, *exception = NULL, *value = NULL;
	zval *bind_type = NULL, *condition = NULL, *operation_made = NULL;
	zval *primary_fields = NULL, *primary_field = NULL, *and_word = NULL;
	zval *params = NULL, *class_name = NULL, *type = NULL, *message = NULL;
	zval *r0 = NULL, *r1 = NULL;
	HashTable *ah0, *ah1;
	HashPosition hp0, hp1;
	zval **hd;
	int eval_int;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &record) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	PHALCON_INIT_VAR(option);
	ZVAL_STRING(option, "field", 1);
	
	PHALCON_INIT_VAR(field);
	PHALCON_CALL_METHOD_PARAMS_1(field, this_ptr, "getoption", option, PH_NO_CHECK);
	
	PHALCON_INIT_VAR(dependency_injector);
	PHALCON_CALL_METHOD(dependency_injector, record, "getdi", PH_NO_CHECK);
	
	PHALCON_INIT_VAR(service);
	ZVAL_STRING(service, "modelsMetadata", 1);
	
	PHALCON_INIT_VAR(meta_data);
	PHALCON_CALL_METHOD_PARAMS_1(meta_data, dependency_injector, "getshared", service, PH_NO_CHECK);
	
	PHALCON_INIT_VAR(bind_types);
	array_init(bind_types);
	
	PHALCON_INIT_VAR(bind_data_types);
	PHALCON_CALL_METHOD_PARAMS_1(bind_data_types, meta_data, "getbindtypes", record, PH_NO_CHECK);
	
	PHALCON_INIT_VAR(conditions);
	array_init(conditions);
	
	PHALCON_INIT_VAR(placeholders);
	array_init(placeholders);
	
	PHALCON_INIT_VAR(number);
	ZVAL_LONG(number, 0);
	if (Z_TYPE_P(field) == IS_ARRAY) { 
		if (!phalcon_valid_foreach(field TSRMLS_CC)) {
			return;
		}
		
		ah0 = Z_ARRVAL_P(field);
		zend_hash_internal_pointer_reset_ex(ah0, &hp0);
		fes_8aab_0:
			if(zend_hash_get_current_data_ex(ah0, (void**) &hd, &hp0) != SUCCESS){
				goto fee_8aab_0;
			}
			
			PHALCON_INIT_VAR(compose_field);
			ZVAL_ZVAL(compose_field, *hd, 1, 0);
			eval_int = phalcon_array_isset(bind_data_types, compose_field);
			if (!eval_int) {
				PHALCON_INIT_VAR(exception_message);
				PHALCON_CONCAT_SVS(exception_message, "Column '", compose_field, "\" isn't part of the table columns");
				
				PHALCON_INIT_VAR(exception);
				object_init_ex(exception, phalcon_mvc_model_exception_ce);
				PHALCON_CALL_METHOD_PARAMS_1_NORETURN(exception, "__construct", exception_message, PH_CHECK);
				phalcon_throw_exception(exception TSRMLS_CC);
				return;
			}
			
			PHALCON_INIT_VAR(value);
			PHALCON_CALL_METHOD_PARAMS_1(value, record, "readattribute", compose_field, PH_NO_CHECK);
			
			PHALCON_INIT_VAR(r0);
			PHALCON_CONCAT_VSV(r0, compose_field, " = ?", number);
			phalcon_array_append(&conditions, r0, PH_SEPARATE TSRMLS_CC);
			phalcon_array_append(&placeholders, value, PH_SEPARATE TSRMLS_CC);
			
			PHALCON_INIT_VAR(bind_type);
			phalcon_array_fetch(&bind_type, bind_data_types, compose_field, PH_NOISY_CC);
			phalcon_array_append(&bind_types, bind_type, PH_SEPARATE TSRMLS_CC);
			PHALCON_SEPARATE(number);
			increment_function(number);
			zend_hash_move_forward_ex(ah0, &hp0);
			goto fes_8aab_0;
		fee_8aab_0:
		if(0){}
		
	} else {
		eval_int = phalcon_array_isset(bind_data_types, field);
		if (!eval_int) {
			PHALCON_INIT_VAR(exception_message);
			PHALCON_CONCAT_SVS(exception_message, "Column '", field, "\" isn't part of the table columns");
			
			PHALCON_INIT_VAR(exception);
			object_init_ex(exception, phalcon_mvc_model_exception_ce);
			PHALCON_CALL_METHOD_PARAMS_1_NORETURN(exception, "__construct", exception_message, PH_CHECK);
			phalcon_throw_exception(exception TSRMLS_CC);
			return;
		}
		
		PHALCON_INIT_VAR(value);
		PHALCON_CALL_METHOD_PARAMS_1(value, record, "readattribute", field, PH_NO_CHECK);
		
		PHALCON_INIT_VAR(condition);
		PHALCON_CONCAT_VS(condition, field, " = ?0");
		phalcon_array_append(&conditions, condition, PH_SEPARATE TSRMLS_CC);
		phalcon_array_append(&placeholders, value, PH_SEPARATE TSRMLS_CC);
		
		PHALCON_INIT_VAR(bind_type);
		phalcon_array_fetch(&bind_type, bind_data_types, field, PH_NOISY_CC);
		phalcon_array_append(&bind_types, bind_type, PH_SEPARATE TSRMLS_CC);
		PHALCON_SEPARATE(number);
		increment_function(number);
	}
	
	PHALCON_INIT_VAR(operation_made);
	PHALCON_CALL_METHOD(operation_made, record, "getoperationmade", PH_NO_CHECK);
	if (phalcon_compare_strict_long(operation_made, 2 TSRMLS_CC)) {
		PHALCON_INIT_VAR(primary_fields);
		PHALCON_CALL_METHOD_PARAMS_1(primary_fields, meta_data, "getprimarykeyattributes", record, PH_NO_CHECK);
		if (!phalcon_valid_foreach(primary_fields TSRMLS_CC)) {
			return;
		}
		
		ah1 = Z_ARRVAL_P(primary_fields);
		zend_hash_internal_pointer_reset_ex(ah1, &hp1);
		fes_8aab_1:
			if(zend_hash_get_current_data_ex(ah1, (void**) &hd, &hp1) != SUCCESS){
				goto fee_8aab_1;
			}
			
			PHALCON_INIT_VAR(primary_field);
			ZVAL_ZVAL(primary_field, *hd, 1, 0);
			eval_int = phalcon_array_isset(bind_data_types, primary_field);
			if (!eval_int) {
				PHALCON_INIT_VAR(exception_message);
				PHALCON_CONCAT_SVS(exception_message, "Column '", primary_field, "\" isn't part of the table columns");
				
				PHALCON_INIT_VAR(exception);
				object_init_ex(exception, phalcon_mvc_model_exception_ce);
				PHALCON_CALL_METHOD_PARAMS_1_NORETURN(exception, "__construct", exception_message, PH_CHECK);
				phalcon_throw_exception(exception TSRMLS_CC);
				return;
			}
			
			PHALCON_INIT_VAR(value);
			PHALCON_CALL_METHOD_PARAMS_1(value, record, "readattribute", primary_field, PH_NO_CHECK);
			
			PHALCON_INIT_VAR(condition);
			PHALCON_CONCAT_VSV(condition, primary_field, " <> ?", number);
			phalcon_array_append(&conditions, condition, PH_SEPARATE TSRMLS_CC);
			phalcon_array_append(&placeholders, value, PH_SEPARATE TSRMLS_CC);
			
			PHALCON_INIT_VAR(bind_type);
			phalcon_array_fetch(&bind_type, bind_data_types, primary_field, PH_NOISY_CC);
			phalcon_array_append(&bind_types, bind_type, PH_SEPARATE TSRMLS_CC);
			PHALCON_SEPARATE(number);
			increment_function(number);
			zend_hash_move_forward_ex(ah1, &hp1);
			goto fes_8aab_1;
		fee_8aab_1:
		if(0){}
		
	}
	
	PHALCON_INIT_VAR(and_word);
	ZVAL_STRING(and_word, " AND ", 1);
	
	PHALCON_ALLOC_ZVAL_MM(r1);
	phalcon_fast_join(r1, and_word, conditions TSRMLS_CC);
	PHALCON_CPY_WRT(conditions, r1);
	
	PHALCON_INIT_VAR(params);
	array_init(params);
	phalcon_array_update_string(&params, SL("di"), &dependency_injector, PH_COPY | PH_SEPARATE TSRMLS_CC);
	phalcon_array_update_string(&params, SL("conditions"), &conditions, PH_COPY | PH_SEPARATE TSRMLS_CC);
	phalcon_array_update_string(&params, SL("bind"), &placeholders, PH_COPY | PH_SEPARATE TSRMLS_CC);
	phalcon_array_update_string(&params, SL("bindTypes"), &bind_types, PH_COPY | PH_SEPARATE TSRMLS_CC);
	
	PHALCON_INIT_VAR(class_name);
	phalcon_get_class(class_name, record TSRMLS_CC);
	
	PHALCON_INIT_VAR(number);
	PHALCON_CALL_STATIC_ZVAL_PARAMS_1(number, class_name, "count", params);
	if (!phalcon_compare_strict_long(number, 0 TSRMLS_CC)) {
		PHALCON_INIT_VAR(type);
		ZVAL_STRING(type, "unique", 1);
		
		PHALCON_INIT_VAR(option);
		ZVAL_STRING(option, "message", 1);
		
		PHALCON_INIT_VAR(message);
		PHALCON_CALL_METHOD_PARAMS_1(message, this_ptr, "getoption", option, PH_NO_CHECK);
		if (!zend_is_true(message)) {
			PHALCON_INIT_VAR(message);
			PHALCON_CONCAT_SVS(message, "Value of field '", field, "' is already present in another record");
		}
		
		PHALCON_CALL_METHOD_PARAMS_3_NORETURN(this_ptr, "appendmessage", message, field, type, PH_NO_CHECK);
		PHALCON_MM_RESTORE();
		RETURN_FALSE;
	}
	
	PHALCON_MM_RESTORE();
	RETURN_TRUE;
}

