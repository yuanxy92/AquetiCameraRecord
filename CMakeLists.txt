## CMakeLists.txt for generic camera driver
# author: Shane Yuan
# date: Dec 29, 2017
#

##
##                     _oo0oo_
##                    o8888888o
##                    88" . "88
##                    (| -_- |)
##                    0\  =  /0
##                  ___/`---'\___
##                .' \\|     |// '.
##               / \\|||  :  |||// \
##              / _||||| -:- |||||- \
##             |   | \\\  -  /// |   |
##             | \_|  ''\---/''  |_/ |
##             \  .-\__  '-'  ___/-. /
##           ___'. .'  /--.--\  `. .'___
##        ."" '<  `.___\_<|>_/___.' >' "".
##       | | :  `- \`.;`\ _ /`;.`/ - ` : | |
##       \  \ `_.   \_ __\ /__ _/   .-` /  /
##   =====`-.____`.___ \_____/___.-`___.-'=====
##                     `=---='
##
##             佛祖保佑         永无BUG
##               Buddha Bless No Bug
##

message(
"##
##                     _oo0oo_
##                    o8888888o
##                    88\" . \"88
##                    (| -_- |)
##                    0\\  =  /0
##                  ___/`---'\\___
##                .' \\\\|     |// '.
##               / \\\\|||  :  |||// \\
##              / _||||| -:- |||||- \\
##             |   | \\\\\\  -  /// |   |
##             | \\_|  ''\\---/''  |_/ |
##             \\  .-\\__  '-'  ___/-. /
##           ___'. .'  /--.--\\  `. .'___
##        .\"\" '<  `.___\\_<|>_/___.' >' \"\".
##       | | :  `- \\`.;`\\ _ /`;.`/ - ` : | |
##       \\  \\ `_.   \\_ __\\ /__ _/   .-` /  /
##   =====`-.____`.___ \\_____/___.-`___.-'=====
##                     `=---='
##
##             佛祖保佑         永无BUG
##               Buddha Bless No Bug
##
"
)

cmake_minimum_required (VERSION 3.5.0)
set(name "MantisRecord")
project ( ${name} )

# c++ version
set (CMAKE_CXX_STANDARD 11)

# # project to record h264 streams
# add_executable(RecordStream
#     getFrame.cpp
# )
# target_link_libraries(RecordStream
#     /usr/local/MantisAPI.so
# )

# project to cut recorded h264 streams
# find the first I frame and discard the previous P frames 
add_executable(CutH264Stream
    CutH264Stream.cpp
)

# project to find synchronized frames in h264 streams using time stamps
add_executable(FindSyncFrames
    FindSyncFrames.cpp
)
