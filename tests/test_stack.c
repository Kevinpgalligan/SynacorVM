#include <check.h>
#include "stack.h"

START_TEST(test_push_and_pop) {
    Stack *stack = stack_init();
    unsigned short popped;

    ck_assert(stack_push(stack, 1) == StackOpSuccess);
    ck_assert(stack_push(stack, 2) == StackOpSuccess);
    ck_assert(stack_pop(stack, &popped) == StackOpSuccess);
    ck_assert(popped == 2);
    ck_assert(stack_pop(stack, &popped) == StackOpSuccess);
    ck_assert(popped == 1);
    ck_assert(stack_pop(stack, &popped) == StackNoElementsError);

    stack_free(stack);
}
END_TEST

Suite *stack_suite(void) {
    Suite *s = suite_create("Stack");
    TCase *tc_core = tcase_create("Core");
    
    tcase_add_test(tc_core, test_push_and_pop);

    suite_add_tcase(s, tc_core);

    return s;
}
