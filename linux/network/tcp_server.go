/*
 * @Author: your name
 * @Date: 2022-01-15 23:18:16
 * @LastEditTime: 2022-02-07 18:41:35
 * @LastEditors: Please set LastEditors
 * @Description: tcp监听服务器
 * @FilePath: /comm/linux/network/tcp_server.go
 */
package main

import (
	"fmt"
	"net"
	"runtime"
	// log "github.com/sirupsen/logrus"
)

// func init() {
// 	// Log as JSON instead of the default ASCII formatter.
// 	log.SetFormatter(&log.JSONFormatter{})

// 	// Output to stdout instead of the default stderr
// 	// Can be any io.Writer, see below for File example
// 	log.SetOutput(os.Stdout)

// 	// Only log the warning severity or above.
// 	log.SetLevel(log.WarnLevel)
// }

func main() {
	fmt.Println(runtime.Version())
	fmt.Println("starting the server")

	ls, err := net.Listen("tcp", "127.0.0.1:8080")
	if err != nil {
		fmt.Println("err listen", err.Error())
	}

	sum := 0 //短变量声明

	for {
		_, err := ls.Accept()
		if err != nil {
			fmt.Println("err accept", err.Error())
		}

		sum++
		if 0 == sum%10000 {
			fmt.Println("accept", sum)
		}
	}
}
