#include <mathematics.h>

#include <glib.h>
#include <locale.h>

static void test_subtraction(void)
{
    g_assert_true(90 == subtraction(100, 10));
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");

    g_test_init(&argc, &argv, NULL);

    // Define the tests.
    g_test_add_func("/basic_functionality/subtraction", test_subtraction);

    return g_test_run();
}
