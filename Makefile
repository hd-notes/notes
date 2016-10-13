rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))
tex_files = $(call rwildcard, , *.tex)
pdf_files = $(tex_files:.tex=.pdf)
clean_files = $(tex_files:.tex=.does_not_exist)

%.does_not_exist: %.tex
	latexmk -cd -c -xelatex $<	

%.pdf: %.tex
	latexmk -cd -xelatex $<
	latexmk -cd -c -xelatex $<	

all: $(pdf_files)

.PHONY: clean clobber
clean: $(clean_files)
	find . -name '*.pdf' -delete

clobber: $(clean_files)
