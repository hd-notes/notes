#!/bin/bash
set -e # Exit with nonzero exit code if anything fails

function doCompile {
  ./compile.sh
}

# Enable case-insensitive pattern matching.
shopt -s nocasematch

get_download_url() {
  echo "https://raw.githubusercontent.com/rroohhh/travis-texlive/master/texlive.tar.xz"
}


echo "Downloading portable TeX Live installation..."
curl -s $( get_download_url ) | tar -xJC "${HOME}"

# Ensure PATH points to the platform-specific binaries.
if [[ "${TRAVIS_OS_NAME:-}" == "linux" ]]; then
	export PATH="${HOME}/texlive/bin/x86_64-linux:${PATH}"
else
	export PATH="${HOME}/texlive/bin/x86_64-darwin:${PATH}"
fi

git clone git://orgmode.org/org-mode.git
cd org-mode
make autoloads
make 
sudo make install
cd ..
rm -rf org-mode

# Save some useful information
SHA=`git rev-parse --verify HEAD`

# Clone the existing gh-pages for this repo into out/
# Create a new empty branch if gh-pages doesn't exist yet (should only happen on first deply)
git clone https://github.com/hd-notes/pdfs.git pdfs
git clone https://github.com/hd-notes/hd-notes.github.io.git pages

# Clean out existing contents
# TODO(robin): auto run fetch scripts
# rm -rf pdfs/**/* || exit 0
rm -rf pages/index.html || exit 0

# Run our compile script
doCompile

# Pull requests and commits to other branches shouldn't try to deploy, just build to verify
if [ "$TRAVIS_PULL_REQUEST" != "false" ]; then
    echo "Skipping deploy; just doing a build."
    exit 0
fi

# copy the pdfs
find . ! -path "./pdfs/*" ! -path "./pages/*" -name '*.pdf' -exec dirname {} \; | xargs -I {} mkdir -p pdfs/{} 2> /dev/null
find . ! -path "./pdfs/*" ! -path "./pages/*" -name '*.pdf' -exec cp {} pdfs/{} \;

# Now let's go have some fun with the cloned repo
echo "updating pdfs"
cd pdfs
git config user.name "Travis CI"
git config user.email "$COMMIT_AUTHOR_EMAIL"

# If there are no changes to the compiled out (e.g. this is a README update) then just bail.
# if [ -z `git diff --exit-code` ]; then
#     echo "No changes to the output on this push; exiting."
#     exit 0
# fi

# Commit the "changes", i.e. the new version.
# The delta will show diffs between new and old versions.
git add .
git commit -m "travis auto compile: ${SHA}"

# Get the deploy key by using Travis's stored variables to decrypt deploy_key.enc
openssl aes-256-cbc -K $encrypted_fcdac90c3348_key -iv $encrypted_fcdac90c3348_iv -in ../keys.enc -out keys -d

head -c3243 keys > pdf_key
tail -c3247 keys > ../pages/pages_key
chmod 600 pdf_key
eval `ssh-agent -s`
ssh-add pdf_key

# Now that we're all set up, we can push.
git push git@github.com:hd-notes/pdfs.git
# git push origin master

cd ..

echo "updating pages"
cd pages
./generate.sh ../

git config user.name "Travis CI"
git config user.email "$COMMIT_AUTHOR_EMAIL"

# If there are no changes to the compiled out (e.g. this is a README update) then just bail.
# if [ -z `git diff --exit-code` ]; then
#    echo "No changes to the output on this push; exiting."
#    exit 0
# fi

# Commit the "changes", i.e. the new version.
# The delta will show diffs between new and old versions.
git add .
git commit -m "travis auto update: ${SHA}"

# Get the deploy key by using Travis's stored variables to decrypt deploy_key.enc
# ENCRYPTED_KEY_VAR="encrypted_${ENCRYPTION_LABEL}_key"
# ENCRYPTED_IV_VAR="encrypted_${ENCRYPTION_LABEL}_iv"
# ENCRYPTED_KEY=${!ENCRYPTED_KEY_VAR}
# ENCRYPTED_IV=${!ENCRYPTED_IV_VAR}

chmod 600 pages_key
ssh-add -D
ssh-add pages_key

# Now that we're all set up, we can push.
git push git@github.com:hd-notes/hd-notes.github.io.git
# git push origin master
