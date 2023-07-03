#include <mathematics.h>

#include <glib.h>
#include <locale.h>

static void test_addition(void)
{
    g_assert_true(110 == addition(100, 10));
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");

    g_test_init(&argc, &argv, NULL);

    // Define the tests.
    g_test_add_func("/basic_functionality/addition", test_addition);

    return g_test_run();
}
