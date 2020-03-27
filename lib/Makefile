

EXTERNAL_TARGETS := \
	../external/googletest/googletest/make/gtest_main.a

EXTERNAL_DIRS := $(foreach ext,$(EXTERNAL_TARGETS), $(dir $(ext)))

.PHONY: $(EXTERNAL_TARGETS)


all: libgtest.a

$(EXTERNAL_TARGETS):
	@echo -e "    \e[93m[artefact]\e[0m $@"
	@$(MAKE) -s --no-print-directory  -C $(dir $@)

libgtest.a: ../external/googletest/googletest/make/gtest_main.a
	@echo -e "    \e[92m[library]\e[0m $@"
	@ln -sf $< $@

clean:
	@echo "Cleaning library..."; 
	@$(RM) *.a
	@echo "Cleaning external..."; 
	@for dir in $(EXTERNAL_DIRS); do 	\
		$(MAKE) -s --no-print-directory  -C $$dir clean;			\
	done
