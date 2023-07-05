#include <mathematics.h>
#include <glib/glib.h>
#include <stdbool.h>

static gchar* executable;

static gboolean help;
static int num1 = 0;
static int num2 = 0;

/* Error Reporting */
static void print_errorv(const char *fmt, va_list args)
{
    g_fprintf(stderr, "%s: ", g_get_prgname());
    g_vfprintf(stderr, fmt, args);
    g_fprintf(stderr, "\n");
}

void print_error(const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    print_errorv(fmt, args);
    va_end(args);
}

/* Display the Help */
static void show_help(GOptionContext *opt_ctx)
{
    char *help_str = g_option_context_get_help(opt_ctx, false, NULL);
    fwrite(help_str, 1, strlen(help_str), stdout);
    g_free(help_str);
}

/* Parse the CLI options handling '--help' */
static bool parse_options(GOptionContext *opt_ctx, int *argc, char ***argv,
                          int *status)
{
    GError *gerror = NULL;
    bool rc = g_option_context_parse(opt_ctx, argc, argv, &gerror);

    g_assert(status);

    if (!rc) {
        print_error("Option parsing failed: %s", gerror->message);
        g_error_free(gerror);
        *status = -1;
    } else if (help) {
        show_help(opt_ctx);
        *status = 0;
        rc = false;
    }

    return rc;
}

/* Main option parameters */
const char *common_contact = "Contact: sunilsharma.pv@gmail.com";

static const char *main_parameters = "<command> <command-opts>";

static const char *main_summary =
        "A Mathematics Library\n"
        "\n"
        "Supported Commands:\n"
        "\n"
        "  add      Addition of two numbers\n"
        "  sub      Subtraction of two numbers\n"
        "  mul      Multiplication of two numbers\n"
        "  div      Division of two numbers\n"
        "\n"
        "Run '%s <command> --help' for command specific help";

static GOptionEntry common_options[] = {
        {"help", 'h', G_OPTION_FLAG_NONE, G_OPTION_ARG_NONE, &help,
         "Show help options and exit.", NULL},
        {NULL},
};

static GOptionContext *common_option_context(const char *parameter_string,
                                             const char *summary, bool strict)
{
    GOptionContext *opt_ctx;

    opt_ctx = g_option_context_new(parameter_string);

    g_option_context_set_help_enabled(opt_ctx, false);
    g_option_context_set_summary(opt_ctx, summary);
    g_option_context_set_description(opt_ctx, common_contact);
    g_option_context_add_main_entries(opt_ctx, common_options, NULL);
    g_option_context_set_strict_posix(opt_ctx, strict);

    return opt_ctx;
}

/* Addition section */
static const char *add_parameters = "add <add options>";

static const char *add_summary = "Adds num1 and num2";

static GOptionEntry add_options[] = {
        {"num1", 'm', G_OPTION_FLAG_NONE, G_OPTION_ARG_INT, (void *)&num1,
         "An Integer", "NUM"},
        {"num2", 'n', G_OPTION_FLAG_NONE, G_OPTION_ARG_INT, (void *)&num2,
         "An Integer", "NUM"},
        {NULL},
};

static int add(int argc, char **argv)
{
    GOptionContext *opt_ctx;
    GOptionGroup *group;
    int rc = 0;

    opt_ctx = common_option_context(add_parameters, add_summary, false);

    group = g_option_group_new("add", "add options:", "", NULL, NULL);

    g_option_group_add_entries(group, add_options);
    g_option_context_add_group(opt_ctx, group);

    if (argc <= 1) {
        print_error("ERROR: No arguments given. See 'math_cli add -h' for help");
        rc = -1;
        goto cleanup;
    }

    if (!parse_options(opt_ctx, &argc, &argv, &rc)) {
        goto cleanup;
    }

    g_printf("%d + %d = %d\n", num1, num2, addition(num1, num2));

cleanup:
    g_option_context_free(opt_ctx);
    return rc;
}

/* Subtraction section */
static const char *sub_parameters = "sub <sub options>";

static const char *sub_summary = "Subtracts num2 from num1";

static GOptionEntry sub_options[] = {
        {"num1", 'm', G_OPTION_FLAG_NONE, G_OPTION_ARG_INT, (void *)&num1,
         "An Integer", "NUM"},
        {"num2", 'n', G_OPTION_FLAG_NONE, G_OPTION_ARG_INT, (void *)&num2,
         "An Integer", "NUM"},
        {NULL},
};

static int sub(int argc, char **argv)
{
    GOptionContext *opt_ctx;
    GOptionGroup *group;
    int rc = 0;

    opt_ctx = common_option_context(sub_parameters, sub_summary, false);

    group = g_option_group_new("sub", "sub options:", "", NULL, NULL);

    g_option_group_add_entries(group, sub_options);
    g_option_context_add_group(opt_ctx, group);

    if (argc <= 1) {
        print_error("ERROR: No arguments given. See 'math_cli sub -h' for help");
        rc = -1;
        goto cleanup;
    }

    if (!parse_options(opt_ctx, &argc, &argv, &rc)) {
        goto cleanup;
    }

    g_printf("%d - %d = %d\n", num1, num2, subtraction(num1, num2));

cleanup:
    g_option_context_free(opt_ctx);
    return rc;
}

/* Multiplication section */
static const char *mul_parameters = "mul <mul options>";

static const char *mul_summary = "Multiplies num1 and num2";

static GOptionEntry mul_options[] = {
        {"num1", 'm', G_OPTION_FLAG_NONE, G_OPTION_ARG_INT, (void *)&num1,
         "An Integer", "NUM"},
        {"num2", 'n', G_OPTION_FLAG_NONE, G_OPTION_ARG_INT, (void *)&num2,
         "An Integer", "NUM"},
        {NULL},
};

static int mul(int argc, char **argv)
{
    GOptionContext *opt_ctx;
    GOptionGroup *group;
    int rc = 0;

    opt_ctx = common_option_context(mul_parameters, mul_summary, false);

    group = g_option_group_new("mul", "mul options:", "", NULL, NULL);

    g_option_group_add_entries(group, mul_options);
    g_option_context_add_group(opt_ctx, group);

    if (argc <= 1) {
        print_error("ERROR: No arguments given. See 'math_cli mul -h' for help");
        rc = -1;
        goto cleanup;
    }

    if (!parse_options(opt_ctx, &argc, &argv, &rc)) {
        goto cleanup;
    }

    g_printf("%d * %d = %d\n", num1, num2, multiplication(num1, num2));

cleanup:
    g_option_context_free(opt_ctx);
    return rc;
}

/* Division section */
static gboolean remainder;
static gboolean quotient;

static const char *div_parameters = "div <div options>";

static const char *div_summary = "Divides num1 by num2";

static GOptionEntry div_options[] = {
        {"num1", 'm', G_OPTION_FLAG_NONE, G_OPTION_ARG_INT, (void *)&num1,
         "An Integer", "NUM"},
        {"num2", 'n', G_OPTION_FLAG_NONE, G_OPTION_ARG_INT, (void *)&num2,
         "An Integer", "NUM"},
        {"remainder", 'r', G_OPTION_FLAG_NONE, G_OPTION_ARG_NONE, (void *)&remainder,
         "Get the remainder", NULL},
        {"quotient", 'q', G_OPTION_FLAG_NONE, G_OPTION_ARG_NONE, (void *)&quotient,
         "Get the quotient", NULL},
        {NULL},
};

static int div(int argc, char **argv)
{
    GOptionContext *opt_ctx;
    GOptionGroup *group;
    int rc = 0;

    opt_ctx = common_option_context(div_parameters, div_summary, false);

    group = g_option_group_new("div", "div options:", "", NULL, NULL);

    g_option_group_add_entries(group, div_options);
    g_option_context_add_group(opt_ctx, group);

    if (argc <= 1) {
        print_error("ERROR: No arguments given. See 'math_cli div -h' for help");
        rc = -1;
        goto cleanup;
    }

    if (!parse_options(opt_ctx, &argc, &argv, &rc)) {
        goto cleanup;
    }

    if(remainder) {
        g_printf("%d %% %d = %d\n", num1, num2, division_r(num1, num2));
    }

    if(quotient) {
        g_printf("%d / %d = %d\n", num1, num2, division_q(num1, num2));
    }

    if(!remainder && !quotient) {
        g_printf("%d / %d = %d\n", num1, num2, division_q(num1, num2));
        g_printf("%d %% %d = %d\n", num1, num2, division_r(num1, num2));
    }
cleanup:
    g_option_context_free(opt_ctx);
    return rc;
}

/* main functin section */
int main(int argc, char **argv)
{
    GError *error = NULL;
    GString *str = NULL;
    GOptionContext *opt_ctx = NULL;
    int rc = 0;

    gchar **splits = g_strsplit(argv[0], G_DIR_SEPARATOR_S, -1);
    executable = g_strdup(splits[g_strv_length(splits)-1]);
    g_strfreev(splits);

    if (argc == 1) {
        print_error("ERROR: No input specified. See '%s --help'",
                    executable);
        goto cleanup;
    }

    str = g_string_new("");
    g_string_printf(str, main_summary, executable);
    opt_ctx = common_option_context(main_parameters, str->str, true);
    g_string_free(str, true);

    if (!parse_options(opt_ctx, &argc, &argv, &rc))
        goto cleanup;

    if (argc <= 1) {
        show_help(opt_ctx);
        goto cleanup;
    }

    /* Skip over the 'command' string */
    argv++;
    argc--;

    if (!g_strcmp0(argv[0], "add")) {
        rc = add(argc, argv);
    } else if (!g_strcmp0(argv[0], "sub")) {
        rc = sub(argc, argv);
    } else if (!g_strcmp0(argv[0], "mul")) {
        rc = mul(argc, argv);
    } else if (!g_strcmp0(argv[0], "div")) {
        rc = div(argc, argv);
    } else {
        print_error("ERROR: unrecognized command '%s'", argv[0]);
        rc = -1;
        goto cleanup;
    }

cleanup:
    if(opt_ctx) {
        g_option_context_free(opt_ctx);
    }

    g_free(executable);

    return rc;
}
