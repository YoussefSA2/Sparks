# CONTRIBUTING

# How to make a pull request ?

0) Go back to main branch and update it :
```bash
git checkout main
git pull --rebase
```

1) Create a branch with a name which describe the feature you add, or the bug you want to fix.
Ideally, the name should also include the issue number. Example for a branch which adds map generation :

```bash
git checkout -b feat-12-add-map-generation
```

2) Add your changes to the branch, and commit them. 

```bash
git add src/first_file.c src/include/first_file.h
``` 
or 

```bash
git add src/.
```
(only if you are sure that you want to add all the changes)

Then 
```self
git commit -m "feat: add map generation"
```

Please commit often, a lot of small commits, instead of a big commit with all your changes.

3) Push your branch to the remote repository.

```bash
git push -u origin feat-12-add-map-generation
```

4) Go to the [GitHub repository](https://github.com/YoussefSA2/Sparks) and create a pull request.

And you're done! You just need to wait for one (1) review, then you can merge your pull request.
