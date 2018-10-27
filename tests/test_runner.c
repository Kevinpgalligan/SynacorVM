#include <check.h>

int main(void) {
    int num_failed;
    Suite *s = storage_suite();
    SRunner *runner = srunner_create(s);

    srunner_run_all(runner, CK_NORMAL);
    num_failed = srunner_ntests_failed(runner);
    srunner_free(runner);
    return (num_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
