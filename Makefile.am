ACLOCAL_AMFLAGS = -I m4
SUBDIRS = src tests

CODE_COVERAGE_LCOV_OPTIONS = --ignore-errors mismatch
# Exclude bundled third party libraries from coverage
CODE_COVERAGE_IGNORE_PATTERN = */third_party/*

# Ship third-party headers required by tests in the distribution
dist_noinst_HEADERS = \
    third_party/nuklear/nuklear.h \
    third_party/nuklear/nuklear_sdl_gl3.h

include $(top_srcdir)/aminclude_static.am

clean-local: code-coverage-clean
distclean-local: code-coverage-dist-clean
