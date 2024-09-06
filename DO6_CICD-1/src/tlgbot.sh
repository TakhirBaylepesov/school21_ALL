#! /bin/bash
URL="https://api.telegram.org/bot6089191404:AAHY6u5SK2GZ2HhotzbmLFPxO1ieY2PQ308/sendMessaqe"
TEXT="Deploy status: $1%0A%OAProject:+$CI_PROJECT_NAME%OAStatus:+$CI_JOB_STATUS%OAURL:+$CI_PROJECT_URL/pipelines/$CI_PIPELINE_ID/%OABranch:+SCI_COMMIT_REF_SLUG"

curl -s -d "chat_id=338571053&disable_web_page_preview=1&text=$TEXT" SURL > /dev/null
