
if [ $# -eq 1 ];then
    git add . *
    git commit -m "$1"
    git push gitee master
    git push github master
else
    echo "写明 git commit 的信息：　./update.sh \"xxxxx\""
fi
