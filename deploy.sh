#!/bin/bash
set -e # Exit with nonzero exit code if anything fails

function doCompile {
  ./compile.sh
}

# Pull requests and commits to other branches shouldn't try to deploy, just build to verify
if [ "$TRAVIS_PULL_REQUEST" != "false" ]; then
    echo "Skipping deploy; just doing a build."
    doCompile
    exit 0
fi

# Save some useful information
PDF_REPO=${https://github.com/hd-notes/pdfs.git/https:\/\/github.com\//git@github.com:}
PAGES_REPO=${https://github.com/hd-notes/hd-notes.github.io.git/https:\/\/github.com\//git@github.com:}
SHA=`git rev-parse --verify HEAD`

# Clone the existing gh-pages for this repo into out/
# Create a new empty branch if gh-pages doesn't exist yet (should only happen on first deply)
echo $PDF_REPO
echo $PAGES_REPO
git clone $PDF_REPO pdfs
git clone $PAGES_REPO pages

# Clean out existing contents
rm -rf pdfs/**/* || exit 0
rm -rf pages/index.html || exit 0

# Run our compile script
doCompile

# copy the pdfs
find . ! -path "./pdfs/*" ! -path "./pages/*" -name '*.pdf' -exec dirname {} \; | xargs -I {} mkdir pdfs/{} 2> /dev/null
find . ! -path "./pdfs/*" ! -path "./pages/*" -name '*.pdf' -exec cp {} pdfs/{} \;

# Now let's go have some fun with the cloned repo
cd pdfs
git config user.name "Travis CI"
git config user.email "$COMMIT_AUTHOR_EMAIL"

# If there are no changes to the compiled out (e.g. this is a README update) then just bail.
if [ -z `git diff --exit-code` ]; then
    echo "No changes to the output on this push; exiting."
    exit 0
fi

# Commit the "changes", i.e. the new version.
# The delta will show diffs between new and old versions.
git add .
git commit -m "travis auto compile: ${SHA}"

# Get the deploy key by using Travis's stored variables to decrypt deploy_key.enc
ENCRYPTED_KEY_VAR="encrypted_${ENCRYPTION_LABEL}_key"
ENCRYPTED_IV_VAR="encrypted_${ENCRYPTION_LABEL}_iv"
ENCRYPTED_KEY=${!ENCRYPTED_KEY_VAR}
ENCRYPTED_IV=${!ENCRYPTED_IV_VAR}
openssl aes-256-cbc -K $ENCRYPTED_KEY -iv $ENCRYPTED_IV -in ../pdf_key.enc -out pdf_key -d
chmod 600 pdf_key
eval `ssh-agent -s`
ssh-add pdf_key

# Now that we're all set up, we can push.
git push $PDFS_REPO master

cd ..
cd pages
./generate.sh ../

git config user.name "Travis CI"
git config user.email "$COMMIT_AUTHOR_EMAIL"

# If there are no changes to the compiled out (e.g. this is a README update) then just bail.
if [ -z `git diff --exit-code` ]; then
    echo "No changes to the output on this push; exiting."
    exit 0
fi

# Commit the "changes", i.e. the new version.
# The delta will show diffs between new and old versions.
git add .
git commit -m "travis auto update: ${SHA}"

# Get the deploy key by using Travis's stored variables to decrypt deploy_key.enc
ENCRYPTED_KEY_VAR="encrypted_${ENCRYPTION_LABEL}_key"
ENCRYPTED_IV_VAR="encrypted_${ENCRYPTION_LABEL}_iv"
ENCRYPTED_KEY=${!ENCRYPTED_KEY_VAR}
ENCRYPTED_IV=${!ENCRYPTED_IV_VAR}
openssl aes-256-cbc -K $ENCRYPTED_KEY -iv $ENCRYPTED_IV -in ../pages_key.enc -out pages_key -d
chmod 600 pages_key
eval `ssh-agent -s`
ssh-add pages_key

# Now that we're all set up, we can push.
git push $PAGES_REPO master
