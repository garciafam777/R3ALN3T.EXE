#!/usr/bin/env python3
"""One-off MCP introspection: list all tools (names + schemas) from the editor MCP server."""
import asyncio, json
from mcp.client.streamable_http import streamablehttp_client
from mcp import ClientSession

MCP_URL = "http://127.0.0.1:8000/mcp"

async def main():
    async with streamablehttp_client(MCP_URL) as (r, w, _):
        async with ClientSession(r, w) as s:
            await s.initialize()
            # Direct MCP protocol calls (bypassing the bridge's call_tool wrapper)
            tools = await s.list_tools()
            print("TOTAL TOOLS:", len(tools.tools))
            for t in tools.tools:
                nm = t.name
                desc = (t.description or "")[:90].replace("\n", " ")
                print(f"  {nm}  ::  {desc}")

asyncio.run(main())
