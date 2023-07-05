#include <mathematics.h>

#include <glib.h>
#include <locale.h>

static void test_division(void)
{
    g_assert_true(1 == division_r(100, 0));
    g_assert_true(1 == division_q(100, 0));
    g_assert_true(0 == division_r(100, 10));
    g_assert_true(10 == division_q(100, 10));
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");

    g_test_init(&argc, &argv, NULL);

    // Define the tests.
    g_test_add_func("/basic_functionality/division", test_division);

    return g_test_run();
}
