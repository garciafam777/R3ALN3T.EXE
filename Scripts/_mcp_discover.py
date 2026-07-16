import json, subprocess, sys
BR="Scripts/mcp_bridge.py"
# call meta tools
for tool in ["list_toolsets","describe_toolset"]:
    try:
        out=subprocess.run(["python",BR,tool,"{}"],capture_output=True,text=True,timeout=60).stdout
    except Exception as e:
        print(tool,"ERR",e); continue
    print("==== ",tool," ====")
    print(out[:2500])
