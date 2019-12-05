git init
git --bare init

git clone
git add .
git commit -a -m 'init'
git push

git stash
git checkout -b new-branch
git stash apply

git reset
git reset HEAD
git reset HEAD^
