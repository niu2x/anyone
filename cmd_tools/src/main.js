#!/usr/bin/env node

import {
  Command
} from 'commander';

import path from "path"
import fs from "fs";


const program = new Command();

program
  .name('anyone')


program.command("init")
  .argument('<dir>', 'project directory')
  .action((dir) => {
    const configPath = path.join(dir, "project.json")
    const projectConfig = {
      "name": "Anyone Game",
      "entry": "src/entry.lua"
    }
    fs.writeFileSync(configPath, JSON.stringify(projectConfig, null, "  "))
  })

program.command("run")
  .argument('<dir>', 'project directory')
  .action((dir) => {
    console.log(`init ${dir}`)
  })

// registerSubCommand(program)
program.parse(process.argv);