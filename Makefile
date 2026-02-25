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

# force-bootstrap required PROS templates
BOOTSTRAP_REQUIRED_TEMPLATES:=kernel@4.2.2 liblvgl@9.2.0
BOOTSTRAP_OPTIONAL_TEMPLATES:=LemLib@0.5.6
BOOTSTRAP_KERNEL_VERSION:=$(patsubst kernel@%,%,$(firstword $(BOOTSTRAP_REQUIRED_TEMPLATES)))

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

.PHONY: force-bootstrap print-bootstrap-config
print-bootstrap-config:
	@echo "BOOTSTRAP_REQUIRED_TEMPLATES=$(BOOTSTRAP_REQUIRED_TEMPLATES)"
	@echo "BOOTSTRAP_OPTIONAL_TEMPLATES=$(BOOTSTRAP_OPTIONAL_TEMPLATES)"
	@echo "BOOTSTRAP_KERNEL_VERSION=$(BOOTSTRAP_KERNEL_VERSION)"

force-bootstrap:
	@echo "[force-bootstrap] Re-applying PROS templates..."
	@set -e; \
	case "$(firstword $(BOOTSTRAP_REQUIRED_TEMPLATES))" in \
		kernel@*) ;; \
		*) \
			echo "[force-bootstrap] Error: BOOTSTRAP_REQUIRED_TEMPLATES must start with kernel@<version>."; \
			exit 2; \
			;; \
	esac; \
	if [ ! -f project.pros ]; then \
		echo "[force-bootstrap] Initializing PROS project metadata..."; \
		pros c new-project . v5 $(BOOTSTRAP_KERNEL_VERSION) --no-default-libs --force-system; \
	else \
		echo "[force-bootstrap] PROS project metadata already present; skipping initialization."; \
	fi; \
	for template in $(BOOTSTRAP_REQUIRED_TEMPLATES); do \
		echo "[force-bootstrap] Applying $$template"; \
		pros c apply "$$template" --project . --install --download --force --force-apply; \
	done; \
	set +e; \
	for template in $(BOOTSTRAP_OPTIONAL_TEMPLATES); do \
		echo "[force-bootstrap] Applying $$template (optional)"; \
		if ! pros c apply "$$template" --project . --install --download --force --force-apply; then \
			echo "[force-bootstrap] Warning: $$template failed to apply. Skipping."; \
		fi; \
	done; \
	if git rev-parse --is-inside-work-tree >/dev/null 2>&1; then \
		if git ls-files --error-unmatch .gitignore >/dev/null 2>&1; then \
			echo "[force-bootstrap] Restoring .gitignore from git restore"; \
			git restore --source=HEAD -- .gitignore; \
		else \
			echo "[force-bootstrap] Warning: .gitignore is not tracked; skipping restore."; \
		fi; \
	else \
		echo "[force-bootstrap] Warning: Not a git repo; skipping .gitignore restore."; \
	fi

.DEFAULT_GOAL=quick

################################################################################
################################################################################
########## Nothing below this line should be edited by typical users ###########
-include ./common.mk
