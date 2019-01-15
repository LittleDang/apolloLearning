### 20190119
### 今天重新编译了两次apollo，有点坑
 1. 由于apollo是用bazel编译的，又由于在root模式和非root模式下，bazel产生的缓存路径是不一样的。在root模式下缓存是装在**虚拟机里的/root**路径下，在非root模式下缓存是装在**宿主机器的home/.cache**下的，由于apollo只是挂载了本机的apollo这个文件夹，其余默认是自带的，也就是不保存的情况，使用root模式的话，每一次都是要冲行编译的的，所以建议不采用**root模式编译apollo**。
2. docker的保存，只要每次都保存tag为lastest就可以使用-l启动本地的镜像，保存docker镜像的方法
```bash
docker commit -m="message" ID/name images:tag
```
eg
```bash
docker commit -m="build" apollo_dev apolloauto/apollo:loacl_dev 
```
3.一些常用的docker命令
* 显示正在运行的docker
```bash
docker ps
```
* 停止容器
```bash
docker stop apollo_dev
```
* 进入容器
```
sudo docker run -itd ubuntu:14.04 /bin/bash  
```
### 一些git指令
* 更新状态.git `git add .`
* 查看状态`git status`
* 克隆仓库 `git clone`
* 修改 `commit -m ""`
* 上传`git push origin master`