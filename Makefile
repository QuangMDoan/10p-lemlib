################################################################################
######################### User configurable parameters #########################
# filename extensions
CEXTS:=c
ASMEXTS:=s S
CXXEXTS:=cpp c++ cc

# probably shouldn't modify these, but you may need them below
ROOT=.
FWDIR:=$(ROOT)/firmware
BINDIR=$(ROOT)/bin
SRCDIR=$(ROOT)/src
INCDIR=$(ROOT)/include

WARNFLAGS+=
EXTRA_CFLAGS=
EXTRA_CXXFLAGS=

# Set to 1 to enable hot/cold linking
USE_PACKAGE:=1

# Add libraries you do not wish to include in the cold image here
# EXCLUDE_COLD_LIBRARIES:= $(FWDIR)/your_library.a
EXCLUDE_COLD_LIBRARIES:= 

# Auto-bootstrap required PROS templates only when firmware assets are missing
BOOTSTRAP_FIRMWARE_MARKER:=$(FWDIR)/v5.ld
BOOTSTRAP_REQUIRED_TEMPLATES:=kernel@4.2.2 liblvgl@9.2.0
BOOTSTRAP_OPTIONAL_TEMPLATES:=LemLib@0.5.6

# Set this to 1 to add additional rules to compile your project as a PROS library template
IS_LIBRARY:=0
# TODO: CHANGE THIS! 
# Be sure that your header files are in the include directory inside of a folder with the
# same name as what you set LIBNAME to below.
LIBNAME:=libbest
VERSION:=1.0.0
# EXCLUDE_SRC_FROM_LIB= $(SRCDIR)/unpublishedfile.c
# this line excludes opcontrol.c and similar files
EXCLUDE_SRC_FROM_LIB+=$(foreach file, $(SRCDIR)/main,$(foreach cext,$(CEXTS),$(file).$(cext)) $(foreach cxxext,$(CXXEXTS),$(file).$(cxxext)))

# files that get distributed to every user (beyond your source archive) - add
# whatever files you want here. This line is configured to add all header files
# that are in the directory include/LIBNAME
TEMPLATE_FILES=$(INCDIR)/$(LIBNAME)/*.h $(INCDIR)/$(LIBNAME)/*.hpp

.PHONY: bootstrap force-bootstrap
bootstrap:
	@if [ ! -f "$(BOOTSTRAP_FIRMWARE_MARKER)" ]; then \
		echo "[bootstrap] Missing $(BOOTSTRAP_FIRMWARE_MARKER). Re-applying PROS templates..."; \
		set -e; \
		for template in $(BOOTSTRAP_REQUIRED_TEMPLATES); do \
			echo "[bootstrap] Applying $$template"; \
			pros c apply "$$template" --project . --install --download; \
		done; \
		set +e; \
		for template in $(BOOTSTRAP_OPTIONAL_TEMPLATES); do \
			echo "[bootstrap] Applying $$template (optional)"; \
			if ! pros c apply "$$template" --project . --install --download; then \
				echo "[bootstrap] Warning: $$template failed to apply. Skipping."; \
			fi; \
		done; \
	else \
		echo "[bootstrap] Firmware present. Skipping template apply."; \
	fi

force-bootstrap:
	@echo "[force-bootstrap] Re-applying PROS templates..."
	@set -e; \
	for template in $(BOOTSTRAP_REQUIRED_TEMPLATES); do \
		echo "[force-bootstrap] Applying $$template"; \
		pros c apply "$$template" --project . --install --download --force-apply; \
	done; \
	set +e; \
	for template in $(BOOTSTRAP_OPTIONAL_TEMPLATES); do \
		echo "[force-bootstrap] Applying $$template (optional)"; \
		if ! pros c apply "$$template" --project . --install --download --force-apply; then \
			echo "[force-bootstrap] Warning: $$template failed to apply. Skipping."; \
		fi; \
	done

quick: bootstrap

.DEFAULT_GOAL=quick

################################################################################
################################################################################
########## Nothing below this line should be edited by typical users ###########
-include ./common.mk
