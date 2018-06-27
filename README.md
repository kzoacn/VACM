## VACM 

### 演示说明

#### 展示病毒功能

#### 

##### step1

`gcc vv.c -o vv`

`gcc hello.c -o hello`

`gcc aplusb.c -o aplusb`

`vv`是病毒母体,执行完成后有概率断错误

`hello`是简单的hello world

`aplusb`是a+b

##### step2

展示未被感染的`hello`,`aplusb`

`./hello`

`hello`

`./aplusb`

`2 3`

`5`

##### step3

展示感染

`./vv`

每次感染会感染当前目录下一个未被感染的可执行文件

一般来说会按照字典序,如果没有什么意外,`aplusb`会被感染

`infected`
`victim is aplusb`
`infect aplusb`

执行`aplusb`展示其感染`hello`并正常执行旧程序

`./aplusb`

`infected`
`victim is hello`
`infect hello`
`2 3`
`5`

执行`hello`,`vv`虽然是病毒母体但是它并没有被感染,所以会看到

`./hello`

`infected`
`victim is vv`
`infect vv`
`hello`

再次执行,目录下没有可感染程序

`./hello`

`infected`

`hello`



#### 展示Quine与Quine嵌入器

`g++ embeder.cpp -o embeder`

`./embeder <embed.c >quine.c`

`gcc quine.c -o quine`

`quine.c`输出`I am Quine`,并且在文件`myself.c`中输出自身代码

`rm myself.c`

`./quine `

`I am Quine`

`diff quine.c myself.c`

展示`quine.c`与`myself.c`完全相同

