<img src="https://r2cdn.perplexity.ai/pplx-full-logo-primary-dark%402x.png" style="height:64px;margin-right:32px"/>

# How do I enforce the read-only file constraint for Pinokio

To enforce a read-only constraint for Pinokio, use **filesystem permissions plus workflow guardrails**, not just a markdown rule. A “read-only” instruction alone is easy to bypass unless the account running Pinokio is blocked at the OS level from writing to the protected folders.[^1][^2]

## Best enforcement layers

1. **Make the project folders read-only at the OS level.**
    - On Windows, remove write permissions for the user/account that Pinokio runs under.
    - Put production folders under a directory that Pinokio can read but not modify.
    - Keep a separate writable folder for logs or scratch output.
2. **Run Pinokio with a limited account.**
    - Use a dedicated Windows user with no write access to `00_CEO_Brief.md`, `01_Production`, `02_Design`, and other production folders.
    - Give write access only to `13_Logs` if you want it to report startup events.
    - This is much stronger than file attributes alone, which are easy to remove.[^4][^7]
3. **Use a “write whitelist.”**
    - Allow writes only to:
        - `13_Logs/`
        - `99_Archive/` if needed
        - a temporary staging folder
    - Deny writes everywhere else.
4. **Separate read and write paths in your automation.**
    - The agent should read from the project root.
    - Any output should go to a controlled output folder.
    - Never point the agent at the live production tree for write operations.

## Strongest setup for your case

For your studio, I’d use this policy:

- **Read-only:** `00_CEO_Brief.md`, `01_Production`, `02_Design`, `03_Tech`, `04_Art`, `05_QA`, `06_Release`, `07_Comm_Marketing`, `08_IT_DevOps`, `09_Specialists`, `10_Assets`, `11_Builds`, `12_Docs`, `API's`.
- **Writable only by Pinokio:** `13_Logs/`.
- **Writable only by you:** everything else, if needed.

That way Pinokio can log status but cannot alter project direction, assets, or release files.[^3][^10]

## Practical Windows approach

Use one or more of these:

- **NTFS permissions**: deny write/modify to the Pinokio user on protected folders.
- **Separate user account**: launch Pinokio under a restricted account.
- **Controlled folder structure**: keep production in a locked directory and logs in a small writable directory.
- **Version control protection**: require your own approval before Git commits or merges.


## Important warning

Do not rely on the Windows “Read-only” checkbox by itself. That setting is not a true security boundary for folders and is too weak for enforcing agent behavior. True protection comes from permissions and account separation.[^2][^7][^4]

## Recommended rule text

You can put this directly in your startup file:

```md
## File Access Policy
- Pinokio has read-only access to all project files except `13_Logs/`.
- Pinokio may write only to `13_Logs/` and only for startup reports, task logs, and error logs.
- Pinokio may never modify production files, assets, build outputs, or Git history.
- All production changes require human approval and direct execution by an authorized user.
```

Would you like me to write a **Windows permission plan** for your exact `R3ALN3T_UE5` folder tree?
<span style="display:none">[^5][^6][^8][^9]</span>

<div align="center">⁂</div>

[^1]: https://github.com/anomalyco/opencode/issues/2142

[^2]: https://man7.org/linux/man-pages/man7/landlock.7.html

[^3]: https://desktop.pinokio.co/docs/

[^4]: https://www.dummies.com/article/technology/computers/pcs/how-to-change-the-read-only-attribute-on-files-and-folders-184222/

[^5]: https://www.youtube.com/watch?v=YTPjKKKR3Sg

[^6]: https://valkey.io/commands/readonly/

[^7]: https://stackoverflow.com/questions/1333807/how-can-i-make-a-file-trully-immutable-non-deletable-and-read-only

[^8]: https://newreleases.io/project/github/pinokiocomputer/pinokio/release/2.0.2

[^9]: https://newreleases.io/project/github/pinokiocomputer/pinokio/release/3.0.26

[^10]: https://discourse.mcneel.com/t/read-only-files/155259

