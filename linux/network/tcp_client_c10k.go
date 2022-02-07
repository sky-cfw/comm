/*
 * @Author: your name
 * @Date: 2022-02-07 18:53:36
 * @LastEditTime: 2022-02-07 19:15:53
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /comm/linux/network/tcp_client_c10k.go
 */

package main

import (
	"fmt"
	"net"
)

func main() {
	fmt.Println("start to conn server ...")

	cnt := 0

	for {
		_, err := net.Dial("tcp", "141.164.46.98:8080")
		if err != nil {
			fmt.Println("Dial failed", err.Error())
			fmt.Println("conn total num", cnt)
			return
		}

		cnt++
		if cnt%10000 == 0 {
			fmt.Println("conn num", cnt)
		}
	}
}
