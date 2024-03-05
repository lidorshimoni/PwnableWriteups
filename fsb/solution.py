#!/usr/bin/python3 

def make_payload():
    payload = ""
    # payload += "%x," * 30*3
    payload += "LIDOR1\n\x00"
    payload += "LIDOR2\n\x00"
    payload += "LIDOR3\n\x00"
    return payload

def main():
    print(make_payload())



if __name__ == "__main__":
    main()