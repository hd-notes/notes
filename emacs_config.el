(with-eval-after-load 'ox-latex
  (add-to-list 'org-latex-classes
                           '("koma-article"
                                 "\\documentclass{scrartcl}"
                                 ("\\section{%s}" . "\\section*{%s}")
                                 ("\\subsection{%s}" . "\\subsection*{%s}")
                                 ("\\subsubsection{%s}" . "\\subsubsection*{%s}")
                                 ("\\paragraph{%s}" . "\\paragraph*{%s}")
                                 ("\\subparagraph{%s}" . "\\subparagraph*{%s}"))))

(setq org-latex-listings 'minted)
(setq org-latex-minted-options
          '(("tabsize" "4")))

(require 'package)
(add-to-list 'package-archives '("org" . "http://orgmode.org/elpa/"))
(package-initialize)
(package-install 'org)

