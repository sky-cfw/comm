#! /bin/bash

if [ $# -ne 1 ]; then
	echo -e "usage: ./new_branch.sh <branch_name>\nstart to exit!\n"
	exit
fi

echo "start to new branch : $1"

# 更新master
git checkout master && git pull && git checkout -b $1 && git push origin $1:$1 && git branch -a && git branch --set-upstream-to=origin/$1 $1

# 创建本地分支并切换至该分支
#git checkout -b $1

# 将本地分支推送到远程分支
#git push origin $1:$1

# 查看所有分支
#git branch -a

# 将本地分支与远程分支绑定
#git branch --set-upstream-to=origin/$1 $1

echo "new branch $1 succ!"
