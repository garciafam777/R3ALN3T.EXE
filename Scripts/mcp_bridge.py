"""Reusable MCP bridge caller for the R3ALN3T UE editor (http://127.0.0.1:8000/mcp)."""
import asyncio, json, sys
from mcp.client.streamable_http import streamablehttp_client
from mcp import ClientSession

MCP_URL = "http://127.0.0.1:8000/mcp"

async def _call(toolset_name, tool_name, args):
    async with streamablehttp_client(MCP_URL) as (r, w, _):
        async with ClientSession(r, w) as s:
            await s.initialize()
            res = await s.call_tool("call_tool", {
                "toolset_name": toolset_name,
                "tool_name": tool_name,
                "arguments": args,
            })
            text = res.content[0].text if res.content else ""
            return text

def call(toolset_name, tool_name, args):
    return asyncio.run(_call(toolset_name, tool_name, args))

if __name__ == "__main__":
    # usage: python mcp_bridge.py <toolset> <tool> <json_args>
    ts = sys.argv[1]; tn = sys.argv[2]; a = json.loads(sys.argv[3]) if len(sys.argv) > 3 else {}
    print(call(ts, tn, a))
