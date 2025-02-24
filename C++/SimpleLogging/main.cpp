#include "logger.hpp"

int main() {
    Logger log = Logger("LoggetLogging.log", LogLevel::INFO);
    log.debug("Debug level logging");
    log.info("Info level logging at line %d", __LINE__);
    log.warn("warning message on function %s()", __FUNCTION__);
    log.error("error happenning on %s", __TIMESTAMP__);
    log.crit("critical failure happeded at %d", __LINE__);
    log.fatal("fatal failure at line %d on %s from %s()", __LINE__, __TIMESTAMP__, __FUNCTION__);

    log.SetLogLevel(LogLevel::WARNING);
    log.debug("Debug level logging");
    log.info("Info level logging at line %d", __LINE__);
    log.warn("warning message on function %s()", __FUNCTION__);
    log.error("error happenning on %s", __TIMESTAMP__);
    log.crit("critical failure happeded at %d", __LINE__);
    log.fatal("fatal failure at line %d on %s from %s()", __LINE__, __TIMESTAMP__, __FUNCTION__);


    log.SetLogLevel(LogLevel::DEBUG);
    log.debug("Debug level logging");
    log.info("Info level logging at line %d", __LINE__);
    log.warn("warning message on function %s()", __FUNCTION__);
    log.error("error happenning on %s", __TIMESTAMP__);
    log.crit("critical failure happeded at %d", __LINE__);
    log.fatal("fatal failure at line %d on %s from %s()", __LINE__, __TIMESTAMP__, __FUNCTION__);

    printf("%s\n", log.GetLogFileName().c_str());

    return 0;
}
