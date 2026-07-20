import Cookies from 'https://cdn.jsdelivr.net/npm/js-cookie@3.0.8/+esm';

class Setting {
    constructor(name, defaultVal) {
        this.defaultVal = defaultVal;
        if (name.length == 0)
            throw new Error('Empty property name detected');
        this.name = name;
    }

    get() {
        return Cookies.get(this.name) ?? this.defaultVal;
    }

    set(value) {
        return Cookies.set(this.name, value);
    }
}

export let color = new Setting('color', 'turquoise');
export let smallPivot = new Setting('smallPivot', true);
