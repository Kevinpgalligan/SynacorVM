#include <check.h>
#include "storage.h"

START_TEST(test_init_and_free) {
    Storage *s = storage_init();
    storage_free(s);
}
END_TEST

START_TEST(test_memory_initialized_to_zero) {
    Storage *s = storage_init();
    size_t values_to_check = 100;
    unsigned short *values = malloc(values_to_check * sizeof *values);
    MemoryOpStatusCode code = storage_get_mem(s, 0, values_to_check, values);

    ck_assert(code == MemoryOpSuccess);
    for (size_t i = 0; i < values_to_check; i++) {
        ck_assert(values[i] == 0);
    }

    storage_free(s);
}
END_TEST

START_TEST(test_set_and_get_mem) {
    Storage *s = storage_init();
    unsigned short values[] = { 1, 2, 3 };
    unsigned short num_values = (sizeof values) / (sizeof values[0]);
    unsigned short base_address = 5;
    unsigned short *get_values = malloc(num_values * sizeof *get_values);
    MemoryOpStatusCode set_code, get_code;
    
    set_code  = storage_set_mem(s, base_address, num_values, values);
    ck_assert(set_code == MemoryOpSuccess);
    
    get_code = storage_get_mem(s, base_address, num_values, get_values);
    ck_assert(get_code == MemoryOpSuccess);

    for (size_t i = 0; i < num_values; i++) {
        ck_assert(get_values[i] == values[i]);
    }

    free(get_values);
    storage_free(s);
}
END_TEST

START_TEST(test_get_mem_when_out_of_range) {
    Storage *s = storage_init();
    unsigned short *values = malloc(1 * sizeof *values);
    ck_assert_int_eq(MemoryOpInvalidAddress, storage_get_mem(s, 60000, 1, values));
    storage_free(s);
}
END_TEST

Suite *storage_suite(void) {
    Suite *s = suite_create("Storage");
    TCase *tc_core = tcase_create("Core");
    
    tcase_add_test(tc_core, test_init_and_free);
    tcase_add_test(tc_core, test_memory_initialized_to_zero);
    tcase_add_test(tc_core, test_set_and_get_mem);
    tcase_add_test(tc_core, test_get_mem_when_out_of_range);
    tcase_add_test(tc_core, test_load_program);

    suite_add_tcase(s, tc_core);

    return s;
}
