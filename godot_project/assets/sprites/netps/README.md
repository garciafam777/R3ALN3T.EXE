# NetP Sprite Assets

One folder per NetP agent. Replace SVG placeholders with final PNG/WebP art.

## Folder layout

```
netps/
  {NetPName}/
    idle_portrait.svg          # Default roster/creator portrait
    combat_portrait.svg        # Battle pose
    {tier}_{type}_{element}_{pose}.svg
```

## Naming convention

`{tier}_{type}_{element}_{pose}.svg`

Examples:
- `omega_mechanical_static_idle.svg`
- `gamma_guardian_radiant_combat.svg`

## Registered placeholders

| Folder | Role |
|--------|------|
| `Security/` | OMEGA infrastructure defense |
| `SystemAdmin/` | OMEGA infrastructure admin |
| `default/` | Fallback when no specific art exists |

## Resolver

Use `NetPSpriteResolver.load_netp_portrait(data, pose)` from `scripts/assets/netp_sprite_resolver.gd`.
