#include <mathematics.h>

#include <glib.h>
#include <locale.h>

static void test_multiplication(void)
{
    g_assert_true(1000 == multiplication(100, 10));
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");

    g_test_init(&argc, &argv, NULL);

    // Define the tests.
    g_test_add_func("/basic_functionality/multiplication", test_multiplication);

    return g_test_run();
}
