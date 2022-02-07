/*
 * @Author: your name
 * @Date: 2022-02-07 18:53:36
 * @LastEditTime: 2022-02-07 23:21:33
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /comm/linux/network/tcp_client_c10k.go
 */

package main

import (
	"fmt"
	"net"
	"os"
)

func main() {
	argc := len(os.Args)
	if argc < 3 {
		fmt.Println("usage: ./tcp_client_c10k <ip> <port>")
		return
	}

	fmt.Println("start to conn server ...")
	addr := os.Args[1] + ":" + os.Args[2]
	cnt := 0

	for {
		_, err := net.Dial("tcp", addr)
		if err != nil {
			fmt.Println("Dial failed", err.Error())
			fmt.Println("conn total num", cnt)
			return
		}

		cnt++
		fmt.Println("conn num", cnt)
	}
}
