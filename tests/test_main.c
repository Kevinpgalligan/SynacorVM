#include "test_utils.h"
#include <CUnit/Basic.h>

TestSuiteSetup setups[] = {
    set_up_storage_test_suite
};
int NUM_TEST_SUITES = sizeof(setups) / sizeof(setups[0])

int main() {
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_GET_ERROR();
    }
    for (int i = 0; i < NUM_TEST_SUITES; i++) {
        int result = setups[i]();
        if (result == -1) {
            CU_cleanup_registry();
            return CU_get_error();
        }
    }
    
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
