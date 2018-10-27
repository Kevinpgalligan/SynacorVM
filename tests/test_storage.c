#include <check.h>
#include "storage.h"

START_TEST(test_init_and_free) {
    Storage *s = init_storage();
    free_storage(s);
}
END_TEST

Suite *storage_suite(void) {
    Suite *s = suite_create("Storage");
    TCase *tc_core = tcase_create("Core");
    
    tcase_add_test(tc_core, test_init_and_free);
    suite_add_tcase(s, tc_core);

    return s;
}
