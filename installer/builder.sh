#!/bin/bash
cd payload
tar cf ../payload.tar *
cd ..

if [ -e "payload.tar" ]; then
    gzip payload.tar

    if [ -e "payload.tar.gz" ]; then
	chmod 777 payload.tar.gz
        cat decompress.sh payload.tar.gz > examMalware.bsx
    else
        echo "payload.tar.gz does not exist"
        exit 1
    fi
else
    echo "payload.tar does not exist"
    exit 1
fi

echo "examMalware.bsx created"
exit 0
