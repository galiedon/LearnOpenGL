set(CTEST_PROJECT_NAME "LearnOpenGL")
set(CTEST_NIGHTLY_START_TIME "01:00:00 UTC")

set(CTEST_DROP_METHOD "http")
set(CTEST_DROP_SITE "my.cdash.org")
set(CTEST_DROP_LOCATION "/submit.php?project=LearnOpenGL")
set(CTEST_DROP_SITE_CDASH TRUE)

# does the usage message work?
add_test(Usage Debug/bin/LearnOpenGL)


