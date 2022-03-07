#! /bin/bash

if [ $# -ne 2 ]; then
	echo -n "usage: ./rename_branch <old_branch_name> <new_branch_name>\nstart to exist!"
fi

echo "start to rename branch $1 to $2"

# 本地分支重命名 && 删除远程旧分支 && 上传新命名的本地分支 && 将修改后的本地分支与远程分支关联
git branch -m $1 $2  &&  git push --delete origin $1 && git push origin $2  && git branch --set-upstream-to origin/$2

echo "rename branch succ!"
