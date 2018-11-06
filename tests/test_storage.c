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

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = storage_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
