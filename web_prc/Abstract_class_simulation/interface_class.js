class StorageProvider {
    constructor() {
        if (new.target === StorageProvider) {
            throw new Error("Cannot instantiate");
        }
    }

    upload(file) {
        throw new Error("Cannot called");
    }

    download(file_name) {
        throw new Error("Cannot called");
    }
}

class LocalStorageProvider extends StorageProvider{
    upload(file) {
        console.log(file);
    }

    download(file_name) {
        console.log(file);                
    }
}

class CloudStorageProvide extends StorageProvider {
    upload(file) {
        console.log(file);
    }

    download(file_name) {
        console.log(file_name);   
    }
}
