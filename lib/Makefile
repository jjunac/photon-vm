
all: libgtest.a libgtest_main.a libgmock.a

libgtest.a:
	@cd ../external/googletest/ && cmake .
	@$(MAKE) -s --no-print-directory  -C ../external/googletest/
	@echo -e "    \e[92m[library]\e[0m $@"
	@ln -sf ../external/googletest/lib/libgtest.a $@

libgtest_main.a: libgtest.a
	@echo -e "    \e[92m[library]\e[0m $@"
	@ln -sf ../external/googletest/lib/libgtest_main.a $@

libgmock.a: libgtest.a
	@echo -e "    \e[92m[library]\e[0m $@"
	@ln -sf ../external/googletest/lib/libgmock.a $@

