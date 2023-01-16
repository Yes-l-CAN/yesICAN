<Client Messages>
Messages are client-to-server only unless otherwise specified.

### PASS
```cpp
PASS <password>
```

client가 PASS 를 NICK / USER 를 쓰기 전에 사용.

<password> 뒤에 여러 개를 입력할 수 있지만, 결국 마지막이 패스워드로 사용됨. 그리고 이는 client 가 레지스터 하기 전까지 바뀌지 않는다.

만약 입력한 패스워드가 생성할 당시의 패스워드와 동일하지 않으면, ERR_PASSWDMISMATCH (464) 를 출력하고, 연결을 종료한다. (ERROR) 서버는 반드시 이 둘중 하나의 행동을 수행해야 한다.


### NICK
```cpp
NICK <nickname>
  :WiZ NICK Kilroy    // wiz 가 kilroy 로 변경
   :dan-!d@localhost NICK Mamoped
   // dan- 를 Mamoped 로 벼경
```
client에게 새로운 닉네임을 주거나, 기존의 닉네임을 변경하는데에 사용된다. 

입력한 닉네임이 만약 기존에 사용되던 닉네임이라면, ERR_NICKNAMEINUSE numeric 을 issue 하고, 해당 명령을 무시한다.

만약 지원하지 않는 문자들이 들어오면, ERR_ERRONEUSNICKNAME numeric을 issue 하고, 해당 명령을 무시한다. 

서버는 client에게 nick 명령어가 성공적으로 실행되었다는 것을 명시해야 하며, nickname의 변화를 공지해야 한다. 

 old nickname [ [ "!" user ] "@" host ] 

### USER
```cpp
USER <username> 0 * <realname>
USER guest 0 * :Ronnie Reagan
```

username과 새로운 유저의 real name을 지정하기 위한 첫 커넥션이다. 
<realname> 은 반드시 마지막 파라미터여야 한다. 왜냐하면, 이는 SPACE(' ', 0x20) 캐릭터를 포함할 수 있고, 만약 그러하다면, 맨 앞에 ':'(콜론) 을 붙여줘야 한다.

username 의 최소길이는 1이고, empty 한 상태가 될 수 없다.만약 비어있다면, ERR_NEEDMOREPARAMS 에러를 반환하거나, 디폴트 값을 넣어주어야 한다.

두번째와 세번째 파라미터는 반드시 '0' 와 '*'을 전송해야 한다. 이 기호가 뜻하는 의미는, IRC 프로토콜에 따라 다른 의미를 지닐 수 있다.

client는  <username> 나 <realname>에 의미있는 값이 들어 있지 않다면, 반드시 nickname을 <username> 과 <realname>의 대체제로 nickname을 사용해야한다.

기존에 있던 값이 있다면, (값이 중복이 되면) 서버는 ERR_ALREADYREGISTERED 에러를 띄우고, 해당 시도는 fail 이 되어야 한다.

If the client sends a USER command after the server has successfully received a username using the Ident Protocol, the <username> parameter from this command should be ignored in favour of the one received from the identity server.

### PING
```cpp
[<server>] <token>
```

client, server 양측에서 모두 사용 | client <-> Server 서로 연결 상태 및 연결 지연 시간 확인
token 은 빈 문자열이 되면 안 된다.
<during connection registration>
client -x-> server(may accept) 
server -o-> client (must reply)


### PONG
```cpp
USER 
```
PING명령어에 대한 응답.
서버는 반드시 <server> 파라미터를 보내야하고, clients 는 반드시 이를 무시해야 한다.

*** PING 과 PONG은 같은 Token을 사용해야 한다 ***

### QUIT
```cpp
USER 
QUIT [<reason>]

// msg example
:dan-!d@localhost QUIT :Quit: Bye for now!
    ; dan- is exiting the network with
        the message: "Quit: Bye for now!"
```
client와 server간의 연결 종료
server는 ERROR 메세지 회신 후 client에 대한 연결 close
일반적으로 메세지는 quit을 실행한 사용자와 같은 채널을 사용하는 client에만 발송
netsplit발생하는 경우 => 일반적인 QUIT 메세지와 동일한 방식으로 끊긴 client에 대한 메세지 생성

<!-- PING명령어에 대한 응답.
서버는 반드시 <server> 파라미터를 보내야하고, clients 는 반드시 이를 무시해야 한다. -->

### ERROR
```cpp
USER 
ERROR <reason>
```
<!-- PING명령어에 대한 응답.
서버는 반드시 <server> 파라미터를 보내야하고, clients 는 반드시 이를 무시해야 한다. -->

---
[Channel Operations]
채널과 클라이언트 사이에서 사용되는 명령어
### JOIN