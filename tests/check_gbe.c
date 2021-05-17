#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include <emu.h>

START_TEST(test_nothing) {
    int n = 0;
    ck_assert_uint_eq(n, 0);
} END_TEST

Suite *stack_suite() {
    Suite *s = suite_create("stack");
    TCase *tc = tcase_create("core");

    tcase_add_test(tc, test_nothing);
    suite_add_tcase(s, tc);

    return s;
}

int main() {
    Suite *s = stack_suite();
    SRunner *sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    int nf = srunner_ntests_failed(sr);

    srunner_free(sr);

    return nf == 0 ? 0 : -1;
}

