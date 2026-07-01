# 4K Character Creator Spec

## 1. Document purpose

This document defines the character creator used to build, preview, validate, and save NetPs. It is intended for development teams working in a data-driven pipeline and should be kept alongside the project source so it can evolve with the game.

## 2. Feature summary

The character creator must support:

- Identity creation.
- Visual customization.
- Type and element selection.
- Stat display and stat bias preview.
- Program assignment.
- 4K-scaled UI and accessibility.
- Save, load, randomize, and export functions.

The creator should produce a valid character record that can be used directly by gameplay systems.

## 3. User flow

Recommended order:

1. Pick tier.
2. Enter identity.
3. Select type.
4. Select element.
5. Customize body and face.
6. Customize hair and colors.
7. Assign stats or archetype.
8. Choose Programs.
9. Preview.
10. Save or export.

This order reduces cognitive load and matches the way players typically understand a character builder.

## 4. Screen layout

### Layout mode

Desktop-first three-panel layout.

- **Left panel:** identity and body.
- **Center panel:** live preview.
- **Right panel:** type, element, stats, and programs.
- **Bottom bar:** save, randomize, presets, confirm.

### Responsive behavior

- **4K and ultrawide:** expanded three-panel layout.
- **1440p and 1080p:** same structure, tighter margins.
- **Narrow screens:** stack left and right panels into tabs, preserve preview center.

### Layout constraints

- Minimum readable font size at 4K must remain visually large enough for controller and mouse use.
- All primary controls must remain visible without nested modal dependency.
- Preview area must never shrink below a readable hero viewport.

## 5. Component specifications

### Identity panel

**Name / role:** "Identity panel" — collects the core character identity and metadata.

**Purpose:** establish name, class identity, and hierarchy placement.

**Non-goals:** visual body editing, combat tuning.

**Placement / layout**

- Anchor/position: left.
- Relationship to main content: docked.
- Responsiveness: expands vertically with scroll, retains top-aligned header.

**Structural parts**

- Header region.
- Name field.
- ID field.
- Tier selector.
- Faction selector.
- Role selector.
- Pronoun selector.
- Validation status.

**Item / entity model**

- Fields: name, id, tier, faction, role, pronouns.
- States: default, focused, invalid, locked, read-only.

**Behaviors / interactions**

- Name updates live preview title.
- Tier selection changes available visuals and effects.
- Invalid names trigger inline error messaging.
- Locked fields become non-editable for preset or lore-locked entities.

**Data / rendering rules**

- Name must match naming rules for tier and type.
- Tier determines rarity band and available options.
- ID must be unique within the roster.

**Accessibility**

- All fields labeled with visible text and screen-reader labels.
- Tab order must follow top-to-bottom field flow.
- Error text must be programmatically associated with the invalid field.

**Testing hooks**

- `data-test-id="identity-panel"`
- `data-test-id="name-input"`
- `data-test-id="tier-select"`

### Preview panel

**Name / role:** "Preview panel" — renders the NetP in real time.

**Purpose:** show the current character exactly as it will appear in game.

**Non-goals:** data entry, stat editing.

**Placement / layout**

- Anchor/position: center.
- Relationship to main content: fixed focal region.
- Responsiveness: keeps dominant visual priority across all resolutions.

**Structural parts**

- 3D model or portrait viewport.
- Lighting controls.
- Pose/idle state.
- Background theme.
- Frame or rarity border.

**Item / entity model**

- Fields: model, portrait, effects, border_style, background_theme.
- States: loading, active, error, hidden.

**Behaviors / interactions**

- Updates on any character change.
- Supports rotate, zoom, and pose toggle if 3D.
- Shows type and element effects live.

**Data / rendering rules**

- OMEGA units use special visual framing and rare FX.
- Type and element drive palette, glow, and particle style.

**Accessibility**

- Provide a reduced-motion mode.
- Provide a text summary of current selected appearance.
- Ensure controls do not block the preview for screen-reader users.

**Testing hooks**

- `data-test-id="preview-panel"`
- `data-test-id="preview-viewport"`
- `data-test-id="preview-border"`

### Appearance panel

**Name / role:** "Appearance panel" — body, face, hair, and coloration options.

**Purpose:** define physical design.

**Non-goals:** stat logic and combat loadout.

**Placement / layout**

- Anchor/position: left lower section or tabbed subpanel.
- Relationship to main content: docked with internal tabs.

**Structural parts**

- Body tab.
- Face tab.
- Hair tab.
- Color tab.
- Accessory/effect tab.

**Item / entity model**

- Fields: body_type, height, face_shape, eye_type, hair_style, palette, glow.
- States: selectable, previewed, locked, randomizable.

**Behaviors / interactions**

- Sliders update the model immediately.
- Color pickers update secondary hues and accent colors.
- Rare tier options unlock special forms or visual layers.

**Accessibility**

- Slider values must be numerically displayed.
- Color fields need text labels, not color-only meaning.
- Include presets for fast selection.

**Testing hooks**

- `data-test-id="appearance-panel"`
- `data-test-id="hair-tab"`
- `data-test-id="color-picker"`

### Type and element panel

**Name / role:** "Type and element panel" — defines combat identity and thematic class.

**Purpose:** assign naming flavor, stat bias, and visual identity.

**Non-goals:** direct damage calculations.

**Placement / layout**

- Anchor/position: right top.
- Relationship to main content: docked.

**Structural parts**

- Type selector.
- Element selector.
- Alignment display.
- Domain tag.
- Flavor preview.

**Item / entity model**

- Type values: angelic, demonic, mechanical, viral, etc.
- Element values: fire, light, void, lightning, etc.

**Behaviors / interactions**

- Changing type updates allowed name pools and palette themes.
- Changing element updates effect style and name suggestions.
- Type and element together update the preview subtitle.

**Data / rendering rules**

- Type controls stat bias.
- Element controls elemental FX and Program naming roots.

**Accessibility**

- Never rely on color alone to identify type or element.
- Provide plain-text labels and icons.
- Show current selection in a persistent summary.

**Testing hooks**

- `data-test-id="type-panel"`
- `data-test-id="element-panel"`
- `data-test-id="alignment-summary"`

### Stats panel

**Name / role:** "Stats panel" — shows core values and archetype impact.

**Purpose:** make combat identity visible and understandable.

**Non-goals:** tactical battle execution.

**Placement / layout**

- Anchor/position: right middle.
- Relationship to main content: docked.

**Structural parts**

- HP bar.
- ATK bar.
- RAPID bar.
- CHARGE bar.
- DEF bar.
- Base vs modified view toggle.

**Item / entity model**

- Fields: hp, atk, rapid, charge, def.
- States: base, modified, locked, projected.

**Behaviors / interactions**

- Stat changes update instantly when tier or type changes.
- Show tooltips explaining each stat.
- Display both raw number and comparative bar.

**Data / rendering rules**

- Respect your global stat scale.
- OMEGA units may show cap or special-range indicators.

**Accessibility**

- Every stat must have a text number, not just a bar.
- Use high-contrast bar fills and labels.
- Avoid red-green-only differentiation.

**Testing hooks**

- `data-test-id="stats-panel"`
- `data-test-id="hp-stat"`
- `data-test-id="def-stat"`

### Programs panel

**Name / role:** "Programs panel" — assigns active and passive abilities.

**Purpose:** define combat tools and identity flavor.

**Non-goals:** full battle simulation.

**Placement / layout**

- Anchor/position: right lower section.
- Relationship to main content: docked with scrollable list.

**Structural parts**

- Primary Program.
- Secondary Program.
- Passive.
- Ultimate.
- Signature slot.
- Program library.
- Filter/search bar.

**Item / entity model**

- Fields: program_name, program_family, type, element, rarity, cooldown.
- States: available, locked, equipped, restricted.

**Behaviors / interactions**

- Drag/drop or click-to-equip.
- Suggestions based on type and element.
- Limit-equipped rules by tier or progression.

**Data / rendering rules**

- Program names should follow the family/action naming rule.
- OMEGA characters may have exclusive signature programs.

**Accessibility**

- Clear focus order through the list.
- Announce equipped state and restrictions to assistive tech.
- Search field must support keyboard entry and escape clear.

**Testing hooks**

- `data-test-id="programs-panel"`
- `data-test-id="program-search"`
- `data-test-id="primary-program-slot"`

## 6. Data model

Use a structured output schema like this:

```json
{
  "id": "OMEGA-004",
  "name": "Radiant Sentinel",
  "tier": "OMEGA",
  "type": "Angelic",
  "element": "Light",
  "role": "Defender",
  "appearance": {
    "body": {},
    "face": {},
    "hair": {},
    "colors": {}
  },
  "stats": {
    "hp": 2000,
    "atk": 260,
    "rapid": 180,
    "charge": 200,
    "def": 180
  },
  "programs": {
    "primary": "Halo Guard",
    "secondary": "Prism Break",
    "passive": "Seraph Ward",
    "ultimate": "Radiant Exile"
  }
}
```

This should be the source of truth for saving, loading, and gameplay import.

## 7. Validation rules

- Name must be unique.
- Tier must map to allowed rarity content.
- Type must be valid for the selected domain rules.
- Element must be valid for the chosen type if restricted.
- Stat totals must remain inside the tier's band.
- Program slots must obey unlock restrictions.
- OMEGA-only content must not appear in regular tiers.

## 8. Accessibility requirements

- Support keyboard-only navigation.
- Support controller navigation.
- Support scalable text.
- Support high contrast mode.
- Support reduced motion.
- Use text labels alongside icons.
- Preserve focus when opening modals or subpanels.
- Provide readable tooltips with sufficient delay and spacing.

These are required to make the creator usable at 4K and beyond.

## 9. Responsive and 4K rules

- Use vector UI where possible.
- Use 2x or 4x assets for detailed textures.
- Scale panels based on viewport, not fixed pixels.
- Keep borders and iconography crisp.
- Avoid overfilling the screen with tiny controls.
- Reserve empty space to preserve clarity on large monitors.

## 10. Testing checklist

### Functional

- Can create a valid character.
- Can edit all visible fields.
- Can save, reload, and export.
- Can randomize and reset.
- Can assign Programs correctly.

### Visual

- UI remains sharp at 4K.
- Text remains readable.
- Preview updates correctly.
- No clipping at standard and ultrawide ratios.

### Accessibility

- All controls are keyboard reachable.
- Labels are readable by screen readers.
- Contrast remains sufficient.
- Motion reduction works.

## 11. Development notes

- Keep this file in version control.
- Update the spec when fields or rules change.
- Treat panel names and IDs as stable contracts.
- Separate appearance data from combat data.
- Prefer data-driven content over hardcoded character logic.

**Implementation paths (Godot):**

- Data resource: `godot_project/scripts/character_creator/netp_data.gd`
- Validator: `godot_project/scripts/character_creator/netp_validator.gd`
- Scene: `godot_project/scenes/ui/character_creator/character_creator.tscn`
- Content: `godot_project/data/netp_content.json`
