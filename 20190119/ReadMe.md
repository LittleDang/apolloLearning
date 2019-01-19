### 20190119
今天重新git clone 了一个仓库，和之前clone的仓库对比发现，编译完apollo除了会多出bazel-apollo/bazel-bin/bazel-genfiles/bazel-out/bazel-testlogs这几个编译链接到bazel缓存区的文件外，还多了一个关键的文件夹** py_proto **,之前打开这个文件夹，基本每一个moudules里面的每个子文件都会对应在里面有一个文件，每一个proto文件都会在对应的位置生成对应的 **_pb2.py文件，但是我后来自己添加的文件却没有产生对应的py文件，有点奇怪，更奇怪的是我一开始随便写得一个却产生了对应的文件，我尝试着更改了文件名，但是对应的py文件名却没有更改，然后我发现里面的文件还有一把锁，即是在root权限下创建的，我执行
```bash
bash apollo.sh clean
```
发现py_proto文件夹还在，于是继续执行
```bash
sudo chmod 777 py_proto/*/*/*
```
对应的锁没有了，然后我把py_proto文件夹手动删除，再执行编译语句
```bash
bash apollo.sh build_cpu
```
发现生成了新的py_proto文件夹，并且没有锁，于是我重新编写了测试发送话题的文件，这次执行了三个测试
> 这里的接收指的是可以用rostopic echo 查看
* 发布了RequestHeader话题，这个是apollo原本就有的话题，一直可以发送可以接收
* 发布了ZuoTest话题，这个话题绑定的消息类型也是apollo原本就有的消息类型（似乎是ros自带的消息类型std_msgs\Image)，只是是新的话题而已，猜测可以发送可以接收
* 发布了DangTest话题，这个话题跟之前的测试一样，绑定的消息类型是我自己生成的protobuf（remote_msg.proto）里面的RemoteMessage，之前是可以发送，但是接收不到（猜测是可以发送，但是ros一些东西没设置好，所以接收不到）

之后执行编译，发现三个消息全部可以接收得到。
综上，应该是之前在root模式下执行过编译，导致py_proto文件夹的权限比较高，而apollo.sh build的时候没有权限去修改这个文件夹，而这个文件夹的东西又可能跟ros关系很大。

### 一次作死的经历
猜测，我可以用rostopic查看信息，那么讲道理也可以用rqt查看信息才对，于是机智的我安装了个rqt结果运行的时候找不到master，我才想起apollo根本就没有master，然后我重点是我还commit了。commit完后想起来我rostopic看一下吧，结果发现rostopic坏掉了，很难受。
我运行了
```bash
sudo apt-get autoremove ros-indigo-rqt-graph
```
删除了一下，发现还是不行。那我就换个镜像吧，于是我就用了另一个镜像（原本用的的local_dev，这次用原本的）
```bash
bash docker/scripts/dev_start.sh #没有-l
```
进去里面一切都是新，然而rostopic并不能运行，于是我觉得我镜像没有删除干净，于是果断把所有镜像删除，然后重新下载镜像。
重新进去还是gg的。
直接运行
```bash
bash apollo.sh clean
bash apollo.sh build_cpu #依然不行
```
同时我发现
```bash
bash scripts/diagnostics.sh #也是gg了
```
我意识到整个问题有点严重。

最后重新git clone了整个源,删除所有镜像，就像第一次安装apollo一样干净，仿佛一切都没有发生过，天空依旧那么蓝。
重新编译，解决，rostopic正常了，diagnostics.sh也正常了。