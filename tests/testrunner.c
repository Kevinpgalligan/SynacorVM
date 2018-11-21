#include <check.h>
#include <stdlib.h>

extern Suite *storage_suite(void);
extern Suite *stack_suite(void);

int main(void) {
    int number_failed;
    SRunner *sr;

    sr = srunner_create(storage_suite());
    srunner_add_suite(sr, stack_suite());

    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
