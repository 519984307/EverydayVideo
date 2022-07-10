# EverydayVideo
Random bilibili video player
仅支持Windows系统

Play List：
使用前需要在程序所在目录添加"PlayList.txt"，PlayList会决定程序随机播放的内容
PlayList中每行可填写一个视频的AV/BV号或一名UP主的UID，UP主UID前需添加"UP"以被程序识别
例：
BV1GJ411x7h7
UP8047632
……
若随机选择到UP主，则会从UP主的全部视频中抽取一个播放

权重：
程序使用加权随机数随机播放视频，每个视频权重为100且不可修改，UP主的权重默认为视频总数*100
UP主的权重可以在PlayList中修改，修改方式为：在UP主UID后空格，填写数值，则权重等于该数值。若在数值后添加"V"，则权重等于该数值乘UP主的视频数量
例：使UP主权重为1000
UP8047632 1000
使UP主权重为视频数量*10
UP8047632 10V

运行参数：
无参数或"PLAY_VIDEO" 随机播放视频
"ENABLE_AUTO_RUN" 开启自启动
"DISANLE_AUTO_RUN” 关闭自启动
"ADD_RIGHT_CLICK_MENU_ACTION" 添加右键菜单
"REMOVE_RIGHT_CLICK_MENU_ACTION" 移除右键菜单
