#include "logger.h"
#include "loggerFileBased.h"
#include <filesystem>
#include <direct.h>

using namespace std;
int main() {
    Logger log1 = Logger("LoggerLog1.log", LogLevel::INFO);
    log1.debug("Debug level logging");
    log1.info("Info level logging at line %d", __LINE__);
    log1.warn("warning message on function %s()", __FUNCTION__);
    log1.error("error happenning on %s", __TIMESTAMP__);
    log1.crit("critical failure happeded at %d", __LINE__);
    log1.fatal("fatal failure at line %d on %s from %s()", __LINE__, __TIMESTAMP__, __FUNCTION__);

    log1.SetLogLevel(LogLevel::WARNING);
    log1.debug("Debug level logging");
    log1.info("Info level logging at line %d", __LINE__);
    log1.warn("warning message on function %s()", __FUNCTION__);
    log1.error("error happenning on %s", __TIMESTAMP__);
    log1.crit("critical failure happeded at %d", __LINE__);
    log1.fatal("fatal failure at line %d on %s from %s()", __LINE__, __TIMESTAMP__, __FUNCTION__);


    log1.SetLogLevel(LogLevel::DEBUG);
    log1.debug("Debug level logging");
    log1.info("Info level logging at line %d", __LINE__);
    log1.warn("warning message on function %s()", __FUNCTION__);
    log1.error("error happenning on %s", __TIMESTAMP__);
    log1.crit("critical failure happeded at %d", __LINE__);
    log1.fatal("fatal failure at line %d on %s from %s()", __LINE__, __TIMESTAMP__, __FUNCTION__);

    LoggerFileBased log2;
    log2.LoggerInit("LoggerLog2.log");
    log2.debug("Debug level logging");
    log2.info("Info level logging at line %d", __LINE__);
    log2.warn("warning message on function %s()", __FUNCTION__);
    log2.error("error happenning on %s", __TIMESTAMP__);
    log2.crit("critical failure happeded at %d", __LINE__);
    log2.fatal("fatal failure at line %d on %s from %s()", __LINE__, __TIMESTAMP__, __FUNCTION__);
    return 0;
}
