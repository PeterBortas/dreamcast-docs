Attribute VB_Name = "WSError"
'--------------------------------------------------------
' WSERROR.BAS
'   This file contains Windows Socket error definitions

Global Const WSANOERROR = 10000
Global Const WSAEINTR = 10004
Global Const WSAEBADF = 10009
Global Const WSAEACCES = 10013
Global Const WSAEFAULT = 10014
Global Const WSAEINVAL = 10022
Global Const WSAEMFILE = 10024
Global Const WSAEWOULDBLOCK = 10035
Global Const WSAEINPROGRESS = 10036
Global Const WSAEALREADY = 10037
Global Const WSAENOTSOCK = 10038
Global Const WSAEDESTADDRREQ = 10039
Global Const WSAEMSGSIZE = 10040
Global Const WSAEPROTOTYPE = 10041
Global Const WSAENOPROTOOPT = 10042
Global Const WSAEPROTONOSUPPORT = 10043
Global Const WSAESOCKTNOSUPPORT = 10044
Global Const WSAEOPNOTSUPP = 10045
Global Const WSAEPFNOSUPPORT = 10046
Global Const WSAEAFNOSUPPORT = 10047
Global Const WSAEADDRINUSE = 10048
Global Const WSAEADDRNOTAVAIL = 10049
Global Const WSAENETDOWN = 10050
Global Const WSAENETUNREACH = 10051
Global Const WSAENETRESET = 10052
Global Const WSAECONNABORTED = 10053
Global Const WSAECONNRESET = 10054
Global Const WSAENOBUFS = 10055
Global Const WSAEISCONN = 10056
Global Const WSAENOTCONN = 10057
Global Const WSAESHUTDOWN = 10058
Global Const WSAETOOMANYREFS = 10059
Global Const WSAETIMEDOUT = 10060
Global Const WSAECONNREFUSED = 10061
Global Const WSAELOOP = 10062
Global Const WSAENAMETOOLONG = 10063
Global Const WSAEHOSTDOWN = 10064
Global Const WSAEHOSTUNREACH = 10065
Global Const WSAENOTEMPTY = 10066
Global Const WSAEPROCLIM = 10067
Global Const WSAEUSERS = 10068
Global Const WSAEDQUOT = 10069
Global Const WSAESTALE = 10070
Global Const WSAEREMOTE = 10071
Global Const WSASYSNOTREADY = 10091
Global Const WSAVERNOTSUPPORTED = 10092
Global Const WSANOTINITIALISED = 10093
Global Const WSAHOST_NOT_FOUND = 11001
Global Const WSATRY_AGAIN = 11002
Global Const WSANO_RECOVERY = 11003
Global Const WSANO_DATA = 11004

Public Function WSErrStr(wserr As Integer)

strg = "(unknown)"

Select Case wserr
Case WSAEINTR
    strg = "WSAEINTR"
Case WSAEBADF
    strg = "WSAEBADF"
Case WSAEACCES
    strg = "WSAEACCES"
Case WSAEFAULT
    strg = "WSAEFAULT"
Case WSAEINVAL
    strg = "WSAEINVAL"
Case WSAEMFILE
    strg = "WSAEMFILE"
Case WSAEWOULDBLOCK
    strg = "WSAEWOULDBLOCK"
Case WSAEINPROGRESS
    strg = "WSAEINPROGRESS"
Case WSAEALREADY
    strg = "WSAEALREADY"
Case WSAENOTSOCK
    strg = "WSAENOTSOCK"
Case WSAEDESTADDRREQ
    strg = "WSAEDESTADDRREQ"
Case WSAEMSGSIZE
    strg = "WSAEMSGSIZE"
Case WSAEPROTOTYPE
    strg = "WSAEPROTOTYPE"
Case WSAENOPROTOOPT
    strg = "WSAENOPROTOOPT"
Case WSAEPROTONOSUPPORT
    strg = "WSAEPROTONOSUPPORT"
Case WSAESOCKTNOSUPPORT
    strg = "WSAESOCKTNOSUPPORT"
Case WSAEOPNOTSUPP
    strg = "WSAEOPNOTSUPP"
Case WSAEPFNOSUPPORT
    strg = "WSAEPFNOSUPPORT"
Case WSAEAFNOSUPPORT
    strg = "WSAEAFNOSUPPORT"
Case WSAEADDRINUSE
    strg = "WSAEADDRINUSE"
Case WSAEADDRNOTAVAIL
    strg = "WSAEADDRNOTAVAIL"
Case WSAENETDOWN
    strg = "WSAENETDOWN"
Case WSAENETUNREACH
    strg = "WSAENETUNREACH"
Case WSAENETRESET
    strg = "WSAENETRESET"
Case WSAECONNABORTED
    strg = "WSAECONNABORTED"
Case WSAECONNRESET
    strg = "WSAECONNRESET"
Case WSAENOBUFS
    strg = "WSAENOBUFS"
Case WSAEISCONN
    strg = "WSAEISCONN"
Case WSAENOTCONN
    strg = "WSAENOTCONN"
Case WSAESHUTDOWN
    strg = "WSAESHUTDOWN"
Case WSAETOOMANYREFS
    strg = "WSAETOOMANYREFS"
Case WSAETIMEDOUT
    strg = "WSAETIMEDOUT"
Case WSAECONNREFUSED
    strg = "WSAECONNREFUSED"
Case WSAELOOP
    strg = "WSAELOOP"
Case WSAENAMETOOLONG
    strg = "WSAENAMETOOLONG"
Case WSAEHOSTDOWN
    strg = "WSAEHOSTDOWN"
Case WSAEHOSTUNREACH
    strg = "WSAEHOSTUNREACH"
Case WSAENOTEMPTY
    strg = "WSAENOTEMPTY"
Case WSAEPROCLIM
    strg = "WSAEPROCLIM"
Case WSAEUSERS
    strg = "WSAEUSERS"
Case WSAEDQUOT
    strg = "WSAEDQUOT"
Case WSAESTALE
    strg = "WSAESTALE"
Case WSAEREMOTE
    strg = "WSAEREMOTE"
Case WSASYSNOTREADY
    strg = "WSASYSNOTREADY"
Case WSAVERNOTSUPPORTED
    strg = "WSAVERNOTSUPPORTED"
Case WSANOTINITIALISED
    strg = "WSANOTINITIALISED"
Case WSAHOST_NOT_FOUND
    strg = "WSAHOST_NOT_FOUND"
Case WSATRY_AGAIN
    strg = "WSATRY_AGAIN"
Case WSANO_RECOVERY
    strg = "WSANO_RECOVERY"
Case WSANO_DATA
    strg = "WSANO_DATA"
End Select

WSErrStr = strg
End Function